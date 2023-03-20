#include "core/application.h"

#include <memory>

#include "core/input/events/key_event.h"
#include "core/logger.h"
#include "event/manager.h"

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

        event::Manager::Subscribe<input::KeyPressedEvent>([this](event::Event& event) {
            const auto& key_event {reinterpret_cast<input::KeyPressedEvent&>(event)};
            if (key_event.GetKey() == input::Key::Escape) {
                this->running_ = false;
            }
        });

        if (window_->ShouldClose()) {
            running_ = false;
        }
    }
}

}  // namespace vx::core