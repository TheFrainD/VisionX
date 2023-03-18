#pragma once

#include "core/window.h"

namespace vx::core {

class Application {
public:
    Application();

    void Run();

private:
    Window window_;
    bool running_ {};
};

}  // namespace vx::core