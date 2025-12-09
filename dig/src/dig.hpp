#pragma once

#include "pit/application.hpp"
#include "pit/state.hpp"

class Dig : public pit::Application {
public:
    Dig(pit::State* state);

    void run();

    void update();

    void draw();

private:
    pit::State* state_;
};
