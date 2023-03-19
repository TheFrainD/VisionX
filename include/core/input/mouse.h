#pragma once

#include <array>
#include <glm/glm.hpp>

#include "core/input/codes.h"

namespace vx::core::input {

struct Mouse {
    std::array<bool, static_cast<std::uint16_t>(MouseButton::Last) + 1> buttons;
    glm::vec2 position;
    glm::vec2 previousPosition;
};

}  // namespace vx::core::input