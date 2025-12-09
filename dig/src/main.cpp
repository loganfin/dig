#include "dig.hpp"
#include "pit/state.hpp"

int main()
{
    auto state = pit::State{};
    auto dig = Dig{&state};
    dig.run();
}
