#include "Tools/Wrapper/EventBus.h"
#include <algorithm>

EventBus& EventBus::get_instance() {
  static EventBus instance;
  return instance;
}

EventId EventBus::subscribe(EventType type, const Callback& callback) {
  std::lock_guard<std::mutex> lock(mtx);
  EventId event_id = generate_id();
  subscriptions[type].push_back({.id = event_id, .callback = callback});
  return event_id;
}

void EventBus::unsubscribe(EventId event_id) {
  std::lock_guard<std::mutex> lock(mtx);
  for (auto& [type, handlerList] : subscriptions) {
    auto range = std::ranges::remove_if(
      handlerList,
      [event_id](const Subscription& subscription) {
        return subscription.id == event_id;
      }
    );
    handlerList.erase(range.begin(), range.end());
  }
}

void EventBus::publish(EventType type, const std::string& data) {
  std::lock_guard<std::mutex> lock(mtx);
  auto& subscriptions_by_type = this->subscriptions[type];
  for (const auto& subscription : subscriptions_by_type) {
    subscription.callback(data);
  }
}

EventId EventBus::generate_id() {
  return ++next_id;
}

// void EventBus::print_subscriptions() {
//   for (auto &[type, handlerList] : subscriptions) {
//     std::cout << "Event Type: " << type << std::endl;
//     for (const auto &subscription : handlerList) {
//       std::cout << "  Subscription ID: " << subscription.id << std::endl;
//     }
//   }
// }
// std::ostream &operator<<(std::ostream &os, const EventType &type) {
//   switch (type) {
//   case EventType::DATA:
//     os << "Data";
//     break;
//   case EventType::ERROR:
//     os << "Error";
//     break;
//   }
//   return os;
// }
