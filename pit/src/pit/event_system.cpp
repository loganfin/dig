#include "pit/event_system.hpp"

namespace pit {

EventSystem& EventSystem::instance()
{
    static auto event_system = EventSystem{};
    return event_system;
}

} // namespace pit
