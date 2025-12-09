#pragma once

#include <dlfcn.h>
#include <filesystem>
#include <format>
#include <functional>
#include <mutex>
#include <print>
#include <string>

class SharedLibrary {
public:
    SharedLibrary(std::filesystem::path const& path);

    ~SharedLibrary();

    void reload();

    bool rebuild();

    template <class Signature>
    std::function<Signature> get_function(std::string const& function_name)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        auto* function = reinterpret_cast<std::add_pointer_t<Signature>>(
            dlsym(dl_handle_, function_name.c_str())
        );

        if (!function) {
            std::println(stderr, "{}", dlerror());
            throw std::runtime_error{
                std::format("Failed to load {}\n", function_name)

            };
        }
        std::println("Found function {}", function_name);
        return function;
    }

    void open();

    void close();

private:
    std::filesystem::path path_;
    std::filesystem::path current_path_;
    std::filesystem::path reloaded_plugins_;
    void* dl_handle_ = nullptr;
    mutable std::mutex mutex_;
};
