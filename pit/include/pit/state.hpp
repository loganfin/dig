#pragma once

#include "pit/event_system.hpp"
#include "pit/window.hpp"

#include <atomic>

namespace pit {

class State {
public:
    State();

    ////////////////////////////////////////////////////////////////////////////
    // Systems
    // Game logic should only interact with systems via the state object that
    // it's passed at construction
    Window& window = Window::instance();
    EventSystem& event_system = EventSystem::instance();

    ////////////////////////////////////////////////////////////////////////////
    // Thread safe objects
    // These objects are expected to used from multiple threads (launcher thread
    // and game thread)
    std::atomic<bool> should_exit = false;
};

} // namespace pit
