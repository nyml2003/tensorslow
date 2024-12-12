
#ifndef TORCHLIGHT_COLLECTIONS_COMMON_H
#define TORCHLIGHT_COLLECTIONS_COMMON_H

#include <cstdint>

namespace torchlight::collections {
template <typename T>
class List;

template <typename K, typename V>
class MapEntry;

template <typename K, typename V>
class Map;

class String;

using Byte = uint8_t;

using Unicode = uint32_t;

using Index = uint64_t;

class Integer;
}  // namespace torchlight::collections

#endif  // TORCHLIGHT_COLLECTIONS_COMMON_H
