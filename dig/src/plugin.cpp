
#include "dig.hpp"

#include "pit/plugin.hpp"
#include "pit/state.hpp"

pit::Application* pit::create_application(pit::State* state)
{
    return new Dig{state};
}

void pit::destroy_application(pit::Application* application)
{
    delete application;
}
