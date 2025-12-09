#pragma once

namespace pit {

class Application {
public:
    virtual ~Application() = default;
    virtual void run() = 0;
};

} // namespace pit
