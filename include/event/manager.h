#pragma once

#include <functional>
#include <map>
#include <vector>

#include "event/event.h"

namespace vx::event {

using EventCallback = std::function<void(Event&)>;

class Manager {
public:
    Manager() = delete;

    template <typename T>
    static void Subscribe(EventCallback callback) noexcept {
        static_assert(static_cast<bool>(std::is_base_of_v<Event, T>), "Events must derive from vx::event::Event");
        callbacks_[T::StaticType()].push_back(callback);
    }

    template <typename T, typename... Args>
    static void Post(Args&&... args) noexcept {
        static_assert(static_cast<bool>(std::is_base_of_v<Event, T>), "Events must derive from vx::event::Event");
        T event(std::forward<Args>(args)...);
        Event* base_event = &event;

        if (callbacks_.find(base_event->GetType()) != callbacks_.end()) {
            for (auto&& callback : callbacks_.at(base_event->GetType())) {
                callback(event);
                if (base_event->IsHandled()) {
                    break;
                }
            }
        }

        base_event->SetHandled();
    }

private:
    static std::map<EventType, std::vector<EventCallback>> callbacks_;
};

}  // namespace vx::event