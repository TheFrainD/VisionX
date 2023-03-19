#include "core/input/input.h"

namespace vx::core::input {

Keyboard Input::keyboard_;
Mouse Input::mouse_;

bool Input::IsKeyDown(const Key key) {
    const auto code = static_cast<std::uint16_t>(key);
    if (code > static_cast<std::uint16_t>(Key::Last)) {
        throw InvalidKeyCodeException {key};
    }
    return keyboard_.keys[code];
}

bool Input::IsMouseButtonDown(const MouseButton mouse_button) {
    const auto code = static_cast<std::uint16_t>(mouse_button);
    if (code > static_cast<std::uint16_t>(MouseButton::Last)) {
        throw InvalidMouseButtonCodeException {mouse_button};
    }
    return mouse_.buttons[code];
}

glm::vec2 Input::GetMousePosition() noexcept { return mouse_.position; }

glm::vec2 Input::GetMousePreviousPosition() noexcept { return mouse_.previousPosition; }

}  // namespace vx::core::input
