#include "file_watcher.hpp"
#include "hot_function.hpp"
#include "shared_library.hpp"

#include "pit/application.hpp"
#include "pit/state.hpp"

#include <dlfcn.h>
#include <memory>
#include <print>
#include <thread>

namespace {

std::atomic<bool> s_game_thread_active = false;

} // namespace

int main()
{
    auto lib = SharedLibrary{LIB_DIG_BIN_PATH};
    auto file_watcher = FileWatcher{LIB_DIG_SOURCE_PATH, LIB_DIG_BIN_PATH};

    auto create_application =
        HotFunction<pit::Application*(pit::State*)>(lib, "create_application");
    auto destroy_application =
        HotFunction<void(pit::Application*)>(lib, "destroy_application");

    auto state = std::make_unique<pit::State>();

    bool rebuild_successful = false;
    bool change_detected = false;
    bool startup = true;

    while (!state->should_exit.load()) {
        change_detected = file_watcher.change_detected();

        if (change_detected) {
            std::println("Rebuilding library...");
            rebuild_successful = lib.rebuild();

            if (!state->should_exit.load()) {
                state->should_exit.store(true);
                // Wait for the game thread to exit
                while (s_game_thread_active.load()) {
                    continue;
                }
                state->should_exit.store(false);
            }

            if (rebuild_successful) {
                std::println("Reloading library...");
                lib.reload();

                create_application.update();
                destroy_application.update();
            }
        }

        if (change_detected && rebuild_successful || startup) {
            startup = false;
            std::thread{
                [&create_application, &destroy_application](pit::State* state) {
                    s_game_thread_active.store(true);
                    auto* application = create_application(state);
                    application->run();
                    destroy_application(application);
                    s_game_thread_active.store(false);
                },
                state.get()
            }
                .detach();
        }
    }
}
