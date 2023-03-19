#include "core/input/input.h"

namespace vx::core::input {

bool Input::IsKeyDown(const Key key) const {
    const auto code {static_cast<std::uint16_t>(key)};
    if (code > static_cast<std::uint16_t>(Key::Last)) {
        throw InvalidKeyCodeException {code};
    }
    return keyboard_.keys[code];
}

bool Input::IsMouseButtonDown(const MouseButton mouse_button) const {
    const auto code {static_cast<std::uint16_t>(mouse_button)};
    if (code > static_cast<std::uint16_t>(MouseButton::Last)) {
        throw InvalidMouseButtonCodeException {code};
    }
    return mouse_.buttons[code];
}

glm::vec2 Input::GetMousePosition() const noexcept { return mouse_.position; }

glm::vec2 Input::GetMousePreviousPosition() const noexcept { return mouse_.previousPosition; }

void Input::SetKey(const std::uint16_t code, const bool state) {
    if (code > static_cast<std::uint16_t>(Key::Last)) {
        throw InvalidKeyCodeException {code};
    }
    keyboard_.keys[code] = state;
}

void Input::SetMouseButton(const std::uint16_t code, const bool state) {
    if (code > static_cast<std::uint16_t>(MouseButton::Last)) {
        throw InvalidMouseButtonCodeException {code};
    }
    mouse_.buttons[code] = state;
}

void Input::SetMousePosition(const glm::vec2& position) noexcept {
    mouse_.previousPosition = mouse_.position;
    mouse_.position         = position;
}

}  // namespace vx::core::input
