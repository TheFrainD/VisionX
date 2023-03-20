#pragma once

#include <glm/glm.hpp>

#include "event/event.h"

namespace vx::core::input {

class MouseMovedEvent final : public event::Event {
public:
    VXEVENT(MouseMovedEvent)

    MouseMovedEvent(const glm::vec2& position, const glm::vec2& previous_position)
        : position_(position), previousPosition_(previous_position) {}

    [[nodiscard]] glm::vec2 GetPosition() const noexcept { return position_; }
    [[nodiscard]] glm::vec2 GetPreviousPosition() const noexcept { return previousPosition_; }

private:
    glm::vec2 position_;
    glm::vec2 previousPosition_;
};

class MouseScrolledEvent final : public event::Event {
public:
    VXEVENT(MouseScrolledEvent)

    explicit MouseScrolledEvent(const glm::vec2& offset) : offset_(offset) {}

    [[nodiscard]] glm::vec2 GetOffset() const noexcept { return offset_; }

private:
    glm::vec2 offset_;
};

}  // namespace vx::core::input
