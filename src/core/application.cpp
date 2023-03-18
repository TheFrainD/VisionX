#include "core/application.h"

#include <memory>

#include "core/logger.h"

// Temp
constexpr auto kWindowWidth  = 800;
constexpr auto kWindowHeight = 600;
constexpr auto kWindowTitle  = "VisionX";

namespace vx::core {

Application::Application() {
    Logger::Setup("log.txt");

    window_ = std::make_unique<Window>(kWindowWidth, kWindowHeight, kWindowTitle);
}

void Application::Run() {
    running_ = true;

    while (running_) {
        window_->Update();

        if (window_->ShouldClose()) {
            running_ = false;
        }
    }
}

}  // namespace vx::core