#pragma once

#include "shared_library.hpp"

#include <functional>
#include <mutex>
#include <string>

template <typename Signature>
class HotFunction;

template <typename R, typename... Args>
class HotFunction<R(Args...)> {
public:
    HotFunction(SharedLibrary& library, std::string const& name)
        : library_{library}, name_{name}
    {
        update();
    }

    void update()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        function_ = library_.get_function<R(Args...)>(name_);
    }

    R operator()(Args... args)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!function_)
            throw std::runtime_error("Function not loaded");
        return function_(std::forward<Args>(args)...);
    }

private:
    std::function<R(Args...)> function_;
    SharedLibrary& library_;
    std::string name_;
    mutable std::mutex mutex_;
};
