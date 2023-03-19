#pragma once

#include <exception>
#include <string>

#include "core/input/keyboard.h"
#include "core/input/mouse.h"
#include "core/window.h"

namespace vx::core::input {

class InputException : public std::runtime_error {
public:
    explicit InputException(const std::string& what_arg) : std::runtime_error(what_arg) {}
    explicit InputException(const char* what_arg) : std::runtime_error(what_arg) {}
};

class InvalidKeyCodeException : public InputException {
public:
    explicit InvalidKeyCodeException(const Key key)
        : InputException("Invalid key code given: " + std::to_string(static_cast<std::uint16_t>(key))) {}
};

class InvalidMouseButtonCodeException : public InputException {
public:
    explicit InvalidMouseButtonCodeException(const MouseButton button)
        : InputException("Invalid mouse button code given: " + std::to_string(static_cast<std::uint16_t>(button))) {}
};

class Input {
public:
    Input() = delete;

    [[nodiscard]] static bool IsKeyDown(Key key);
    [[nodiscard]] static bool IsMouseButtonDown(MouseButton mouse_button);

    [[nodiscard]] static glm::vec2 GetMousePosition() noexcept;
    [[nodiscard]] static glm::vec2 GetMousePreviousPosition() noexcept;

private:
    static Keyboard keyboard_;
    static Mouse mouse_;

    friend Window;
};

}  // namespace vx::core::input
