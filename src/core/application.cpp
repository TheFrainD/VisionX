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

    input_  = std::make_shared<input::Input>();
    window_ = std::make_unique<Window>(kWindowWidth, kWindowHeight, kWindowTitle, input_);
}

void Application::Run() {
    running_ = true;

    while (running_) {
        window_->Update();

        if (input_->IsKeyDown(input::Key::Escape)) {
            running_ = false;
        }

        if (window_->ShouldClose()) {
            running_ = false;
        }
    }
}

}  // namespace vx::core