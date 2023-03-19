#pragma once

#include <memory>

#include "core/input/input.h"
#include "core/window.h"

namespace vx::core {

class Application {
public:
    Application();

    void Run();

private:
    std::shared_ptr<input::Input> input_ {};
    std::unique_ptr<Window> window_ {};
    bool running_ {};
};

}  // namespace vx::core