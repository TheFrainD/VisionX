#pragma once

#include <array>

#include "core/input/codes.h"

namespace vx::core::input {

struct Keyboard {
    std::array<bool, static_cast<std::uint16_t>(Key::Last) + 1> keys;
};

}  // namespace vx::core::input