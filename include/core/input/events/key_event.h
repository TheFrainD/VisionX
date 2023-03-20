#pragma once

#include "core/input/codes.h"
#include "event/event.h"

namespace vx::core::input {

class KeyEvent : public event::Event {
public:
    explicit KeyEvent(const Key key) : key_(key) {}

    [[nodiscard]] Key GetKey() const noexcept { return key_; }

private:
    Key key_;
};

class KeyPressedEvent final : public KeyEvent {
public:
    VXEVENT(KeyPressedEvent)

    explicit KeyPressedEvent(const Key key) : KeyEvent(key) {}
};

class KeyReleasedEvent final : public KeyEvent {
public:
    VXEVENT(KeyReleasedEvent)

    explicit KeyReleasedEvent(const Key key) : KeyEvent(key) {}
};

}  // namespace vx::core::input