#include "shared_library.hpp"

namespace {

int s_reload_counter = 0;

auto const s_tmp_lib_path = std::filesystem::path{"reloaded_plugins"};

} // namespace

SharedLibrary::SharedLibrary(std::filesystem::path const& path)
    : path_{path}, reloaded_plugins_{path_.parent_path() / s_tmp_lib_path}
{
    if (std::filesystem::is_directory(reloaded_plugins_)) {
        std::filesystem::remove_all(reloaded_plugins_);
    }
    std::filesystem::create_directory(reloaded_plugins_);
    std::filesystem::create_directory(reloaded_plugins_);

    open();
}

SharedLibrary::~SharedLibrary()
{
    close();

    if (std::filesystem::is_directory(reloaded_plugins_)) {
        std::filesystem::remove_all(reloaded_plugins_);
    }
}

void SharedLibrary::reload()
{
    // TODO: Is the mutex necessary?
    std::lock_guard<std::mutex> lock(mutex_);

    close();
    open();
}

bool SharedLibrary::rebuild()
{
    auto success = system("cmake --build build -t dig") == 0;

    return success;
}

void SharedLibrary::open()
{
    // Move the library to a new directory to avoid the dlopen cache
    current_path_ = reloaded_plugins_ / std::filesystem::path{
                                            path_.filename().string() + "." +
                                            std::to_string(s_reload_counter++)
                                        };
    std::filesystem::copy(path_, current_path_);

    dl_handle_ = dlopen(current_path_.c_str(), RTLD_NOW);
    if (!dl_handle_) {
        throw std::runtime_error(std::string("dlopen failed: ") + dlerror());
    }
}

void SharedLibrary::close()
{
    if (dl_handle_) {
        dlclose(dl_handle_);
        dl_handle_ = nullptr;
    }

    if (!current_path_.empty()) {
        std::filesystem::remove(current_path_);
        current_path_.clear();
    }
}
