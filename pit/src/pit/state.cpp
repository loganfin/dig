#include "pit/state.hpp"

#include <print>

namespace pit {

State::State()
{
    event_system.subscribe<WindowClosedEvent>([this](auto const& event) {
        std::println("WindowClosedEvent received...");
        should_exit.store(true);
    });

    event_system.subscribe<MouseButtonClickedEvent>([](auto const& event) {
        std::println("MouseButtonClickedEvent received...");
        std::print(
            "button: \t{}\naction:\t{}\nmods:\t{}\n",
            event.button,
            event.action,
            event.mods
        );
    });
}

} // namespace pit
