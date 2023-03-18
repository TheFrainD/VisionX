#pragma once

#include <memory>

#include "core/window.h"

namespace vx::core {

class Application {
public:
    Application();

    void Run();

private:
    std::unique_ptr<Window> window_;
    bool running_ {};
};

}  // namespace vx::core