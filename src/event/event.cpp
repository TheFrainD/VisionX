#include "event/event.h"

namespace vx::event {

bool Event::IsHandled() const noexcept { return handled_; }
void Event::SetHandled(const bool handled) noexcept { handled_ = handled; }

}  // namespace vx::event