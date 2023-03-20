#pragma once

#include "core/input/codes.h"
#include "event/event.h"

namespace vx::core::input {

class MouseButtonEvent : public event::Event {
public:
    VXEVENT(MouseButtonEvent)

    explicit MouseButtonEvent(const MouseButton mouse_button) : mouseButton_(mouse_button) {}

    [[nodiscard]] MouseButton GetButton() const noexcept { return mouseButton_; }

private:
    MouseButton mouseButton_;
};

class MouseButtonPressedEvent final : public MouseButtonEvent {
public:
    VXEVENT(MouseButtonPressedEvent)

    explicit MouseButtonPressedEvent(const MouseButton mouse_button) : MouseButtonEvent(mouse_button) {}
};

class MouseButtonReleasedEvent final : public MouseButtonEvent {
public:
    VXEVENT(MouseButtonReleasedEvent)

    explicit MouseButtonReleasedEvent(const MouseButton mouse_button) : MouseButtonEvent(mouse_button) {}
};

}  // namespace vx::core::input