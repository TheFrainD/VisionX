#pragma once

#include <memory>

#include "core/input/events/key_event.h"
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

    void onKeyPressed(input::KeyPressedEvent& event);
};

}  // namespace vx::core