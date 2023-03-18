#include "event/manager.h"

namespace vx::event {

std::map<EventType, std::vector<EventCallback>> Manager::callbacks_;

}  // namespace vx::event
