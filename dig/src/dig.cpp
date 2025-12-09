#include "dig.hpp"

#include <print>
#include <thread>

using namespace std::chrono_literals;

namespace {
}

Dig::Dig(pit::State* state) : state_{state} {}

void Dig::update()
{
    std::println("Hello there");
    std::this_thread::sleep_for(1s);
}

void Dig::draw() {}

void Dig::run()
{
    while (!state_->should_exit.load()) {
        update();
        state_->window.update();
    }
}
