#pragma once

#include <exception>
#include <string>

#include "core/input/events/key_event.h"
#include "core/input/events/mouse_button_event.h"
#include "core/input/events/mouse_event.h"
#include "core/input/keyboard.h"
#include "core/input/mouse.h"

namespace vx::core::input {

class InputException : public std::runtime_error {
public:
    explicit InputException(const std::string& what_arg) : std::runtime_error(what_arg) {}
    explicit InputException(const char* what_arg) : std::runtime_error(what_arg) {}
};

class InvalidKeyCodeException : public InputException {
public:
    explicit InvalidKeyCodeException(const std::uint16_t code)
        : InputException("Invalid key code given: " + std::to_string(code)) {}
};

class InvalidMouseButtonCodeException : public InputException {
public:
    explicit InvalidMouseButtonCodeException(const std::uint16_t code)
        : InputException("Invalid mouse button code given: " + std::to_string(code)) {}
};

class Input {
public:
    [[nodiscard]] bool IsKeyDown(Key key) const;
    [[nodiscard]] bool IsMouseButtonDown(MouseButton mouse_button) const;

    [[nodiscard]] glm::vec2 GetMousePosition() const noexcept;
    [[nodiscard]] glm::vec2 GetMousePreviousPosition() const noexcept;
    [[nodiscard]] glm::vec2 GetScrollOffset() const noexcept;

    void SetKey(Key key, bool state);
    void SetMouseButton(MouseButton mouse_button, bool state);
    void SetMousePosition(const glm::vec2& position) noexcept;
    void SetScrollOffset(const glm::vec2& offset) noexcept;

private:
    Keyboard keyboard_;
    Mouse mouse_;
};

}  // namespace vx::core::input
