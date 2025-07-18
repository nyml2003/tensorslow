#pragma once

#include "Tools/Binding/C_API/c_api.h"

#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

using Callback = std::function<void(std::string)>;

using EventId = uint32_t;

struct Subscription {
  EventId id;
  Callback callback;
};

class EventBus {
 public:
  static EventBus& get_instance();

  // 订阅某个事件类型，返回唯一 EventId
  EventId subscribe(EventType type, const Callback& callback);

  // 根据 EventId 取消订阅
  void unsubscribe(EventId event_id);

  // 发布事件到指定类型
  void publish(EventType type, const std::string& data);

  EventBus(const EventBus&) = delete;
  EventBus& operator=(const EventBus&) = delete;

  EventBus(EventBus&&) = delete;

  EventBus& operator=(EventBus&&) = delete;

 private:
  EventBus() = default;
  ~EventBus() = default;

  EventId generate_id();

  std::unordered_map<EventType, std::vector<Subscription>> subscriptions;
  std::mutex mtx;
  EventId next_id = 0;
};