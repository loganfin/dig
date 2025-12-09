#pragma once

#include "pit/window.hpp"

#include "GLFW/glfw3.h"

#include <string>

namespace pit {

class WindowImpl {
public:
    WindowImpl(std::string const& title, int width, int height);

    ~WindowImpl();

    void update();

    void swap_buffers();

    [[nodiscard]] std::string get_title() const;
    void set_title(std::string const& title);

    [[nodiscard]] int get_width() const;
    void set_width(int width);

    [[nodiscard]] int get_height() const;
    void set_height(int height);

    [[nodiscard]] WindowSize get_size() const;
    void set_size(WindowSize size);

private:
    void register_events();

    GLFWwindow* window_ = nullptr;
};

} // namespace pit

