#include "pit/window.hpp"

#include "pit/window_impl.hpp"

namespace pit {

Window& Window::instance()
{
    static auto window = Window{};
    return window;
}

void Window::update()
{
    window_impl_->update();
}

void Window::swap_buffers()
{
    window_impl_->swap_buffers();
}

std::string Window::get_title() const
{
    return window_impl_->get_title();
}

void Window::set_title(std::string const& title)
{
    window_impl_->set_title(title);
}

int Window::get_width() const
{
    return window_impl_->get_width();
}

void Window::set_width(int width)
{
    window_impl_->set_width(width);
}

int Window::get_height() const
{
    return window_impl_->get_height();
}

void Window::set_height(int height)
{
    window_impl_->set_height(height);
}

WindowSize Window::get_size() const
{
    return window_impl_->get_size();
}

void Window::set_size(WindowSize size)
{
    window_impl_->set_size(size);
}

Window::Window()
    : window_impl_{std::make_unique<WindowImpl>("Pit Game Engine", 1280, 720)}
{
}

} // namespace pit
