#include "core/application.h"

// Temp
constexpr auto kWindowWidth  = 800;
constexpr auto kWindowHeight = 600;
constexpr auto kWindowTitle  = "VisionX";

namespace vx::core {

Application::Application() : window_(kWindowWidth, kWindowHeight, kWindowTitle) {}

void Application::Run() {
    running_ = true;

    while (running_) {
        window_.Update();

        if (window_.ShouldClose()) {
            running_ = false;
        }
    }
}

}  // namespace vx::core