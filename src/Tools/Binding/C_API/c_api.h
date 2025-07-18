// NOLINTBEGIN(*)
#pragma once

#include <cstdint>

// 设置导出/导入符号
#define EVENTBUS_BUILDING_DLL

#if defined(_WIN32)
#if defined(EVENTBUS_BUILDING_DLL)
#define COMPILER_API __declspec(dllexport)
#elif defined(EVENTBUS_USING_DLL)
#define COMPILER_API __declspec(dllimport)
#else
#define COMPILER_API
#endif
#else
#define COMPILER_API __attribute__((visibility("default")))
#endif

// -------------------------------
// 定义所有事件类型（只需在这里添加）
// -------------------------------

#define EVENT_TYPES(F)    \
  F(CONSOLE, 0)           \
  F(ERROR, 1)             \
  F(COMPILER_LEXICAL, 2)  \
  F(COMPILER_SYNTAX, 3)   \
  F(COMPILER_SEMANTIC, 4) \
  F(COMPILER_CODEGEN, 5)  \
  F(VM_FRAME_DUMP, 6)

// -------------------------------
// 生成 C 枚举 EventType
// -------------------------------

typedef enum {
#undef F
#define F(name, val) EVENT_TYPE_##name = val,
  EVENT_TYPES(F)
} C_EventType;

// -------------------------------
// C 接口函数声明
// -------------------------------

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t EventId;
typedef void (*EventCallback)(const char* data);

COMPILER_API EventId
eventbus_subscribe(C_EventType type, EventCallback callback);
COMPILER_API void eventbus_unsubscribe(EventId id);
COMPILER_API void eventbus_publish(C_EventType type, const char* data);

#ifdef __cplusplus
}
#endif

// -------------------------------
// 生成 C++ 枚举类 EventTypeCpp
// -------------------------------

#ifdef __cplusplus

enum class EventType : uint8_t {
#undef F
#define F(name, val) name = (val),
  EVENT_TYPES(F)
};

// 转换函数 C <-> C++
inline C_EventType to_c(EventType type) {
  return static_cast<C_EventType>(type);
}

inline EventType to_cpp(C_EventType type) {
  return static_cast<EventType>(type);
}

#endif  // __cplusplus

// NOLINTEND(*)