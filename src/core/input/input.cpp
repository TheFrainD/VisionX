#include "core/input/input.h"

#include "event/manager.h"

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

void Input::SetKey(const Key key, const bool state) {
    const auto code {static_cast<std::uint16_t>(key)};

    if (code > static_cast<std::uint16_t>(Key::Last)) {
        throw InvalidKeyCodeException {code};
    }

    keyboard_.keys[code] = state;

    if (state) {
        event::Manager::Post<KeyPressedEvent>(key);
    } else {
        event::Manager::Post<KeyReleasedEvent>(key);
    }
}

void Input::SetMouseButton(const MouseButton mouse_button, const bool state) {
    const auto code {static_cast<std::uint16_t>(mouse_button)};

    if (code > static_cast<std::uint16_t>(MouseButton::Last)) {
        throw InvalidMouseButtonCodeException {code};
    }

    mouse_.buttons[code] = state;

    if (state) {
        event::Manager::Post<MouseButtonPressedEvent>(mouse_button);
    } else {
        event::Manager::Post<MouseButtonReleasedEvent>(mouse_button);
    }
}

void Input::SetMousePosition(const glm::vec2& position) noexcept {
    mouse_.previousPosition = mouse_.position;
    mouse_.position         = position;

    event::Manager::Post<MouseMovedEvent>(mouse_.position, mouse_.previousPosition);
}

glm::vec2 Input::GetScrollOffset() const noexcept { return mouse_.scrollOffset; }

void Input::SetScrollOffset(const glm::vec2& offset) noexcept {
    mouse_.scrollOffset = offset;

    event::Manager::Post<MouseScrolledEvent>(mouse_.scrollOffset);
}

}  // namespace vx::core::input
