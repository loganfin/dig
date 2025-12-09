#include "pit/window_impl.hpp"

#include "pit/event_system.hpp"

#include <print>
#include <stdexcept>

namespace pit {
namespace {

void on_window_closed(GLFWwindow* glfw_window);
void on_mouse_button_clicked(GLFWwindow* glfw_window, int, int, int);

} // namespace

WindowImpl::WindowImpl(std::string const& title, int width, int height)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHintString(GLFW_WAYLAND_APP_ID, title.c_str());

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window_) {
        throw std::runtime_error("Failed to create GLFW window!");
    }

    glfwSetWindowUserPointer(window_, this);

    register_events();
}

WindowImpl::~WindowImpl()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void WindowImpl::update()
{
    glfwMakeContextCurrent(window_);
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void WindowImpl::swap_buffers()
{
    glfwSwapBuffers(window_);
}

std::string WindowImpl::get_title() const
{
    return glfwGetWindowTitle(window_);
}

void WindowImpl::set_title(std::string const& title)
{
    glfwSetWindowTitle(window_, title.c_str());
}

int WindowImpl::get_width() const
{
    return get_size().width;
}

void WindowImpl::set_width(int width)
{
    auto size = get_size();
    size.width = width;
    set_size(size);
}

int WindowImpl::get_height() const
{
    return get_size().height;
}

void WindowImpl::set_height(int height)
{
    auto size = get_size();
    size.height = height;
    set_size(size);
}

WindowSize WindowImpl::get_size() const
{
    int width = 0;
    int height = 0;
    glfwGetWindowSize(window_, &width, &height);

    return {.width = width, .height = height};
}

void WindowImpl::set_size(WindowSize size)
{
    glfwSetWindowSize(window_, size.width, size.height);
}

void WindowImpl::register_events()
{
    glfwSetWindowCloseCallback(window_, on_window_closed);
    glfwSetMouseButtonCallback(window_, on_mouse_button_clicked);
}

namespace {

void on_window_closed(GLFWwindow* glfw_window)
{
    std::println("WindowClosedEvent issued...");
    pit::EventSystem::instance().publish<WindowClosedEvent>();
}

void on_mouse_button_clicked(
    GLFWwindow* glfw_window,
    int button,
    int action,
    int mods
)
{
    pit::EventSystem::instance().publish<MouseButtonClickedEvent>(
        button, action, mods
    );
}

} // namespace

} // namespace pit
