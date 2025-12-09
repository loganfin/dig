#pragma once

#include "pit/event_system.hpp"

#include <memory>
#include <string>

namespace pit {

// pimpl is used to avoid making glfw a public dependency
class WindowImpl;

struct WindowSize {
    int width;
    int height;
};

class Window {
public:
    Window(Window const&) = delete;

    Window& operator=(Window const&) = delete;

    static Window& instance();

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
    Window();

    std::unique_ptr<WindowImpl> window_impl_;
};

struct WindowClosedEvent : public Event {};

struct MouseButtonClickedEvent : public Event {
    int button;
    int action;
    int mods;
};

} // namespace pit
