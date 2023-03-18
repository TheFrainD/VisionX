#pragma once

#include <string>

namespace vx::event {
using EventType = std::string;

class Event {
public:
    virtual ~Event() = default;

    Event(const Event&)            = delete;
    Event& operator=(const Event&) = delete;

    Event(Event&&)            = default;
    Event& operator=(Event&&) = default;

    [[nodiscard]] virtual EventType GetType() const noexcept = 0;

    [[nodiscard]] bool IsHandled() const noexcept;
    void SetHandled(bool handled = true) noexcept;

private:
    bool handled_ {};
};

#define VXEVENT(TYPE)                                                                   \
    [[nodiscard]] virtual EventType GetType() const noexcept override { return #TYPE; } \
    static EventType StaticType() noexcept { return #TYPE; }
}  // namespace vx::event