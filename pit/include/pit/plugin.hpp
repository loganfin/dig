#pragma once

#include "pit/application.hpp"
#include "pit/state.hpp"

namespace pit {

extern "C" Application* create_application(State* state);
extern "C" void destroy_application(Application* application);

} // namespace pit
