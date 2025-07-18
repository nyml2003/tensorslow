#include "c_api.h"
#include "Tools/Wrapper/EventBus.h"

extern "C" {

EventId eventbus_subscribe(C_EventType type, EventCallback callback) {
  if (callback == nullptr) {
    return 0;
  }

  return EventBus::get_instance().subscribe(
    to_cpp(type),
    [callback](const std::string& data) { callback(data.c_str()); }
  );
}

void eventbus_unsubscribe(EventId event_id) {
  if (event_id == 0U) {
    return;
  }
  EventBus::get_instance().unsubscribe(event_id);
}

void eventbus_publish(C_EventType type, const char* data) {
  if (data == nullptr) {
    return;
  }
  EventBus::get_instance().publish(to_cpp(type), std::string(data));
}

}  // extern "C"