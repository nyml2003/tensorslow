
#ifndef TORCHLIGHT_COLLECTIONS_COMMON_H
#define TORCHLIGHT_COLLECTIONS_COMMON_H

#include <cstdint>

namespace torchlight::collections {
using Byte = uint8_t;
using Unicode = uint32_t;
using Index = uint64_t;

// overload

}  // namespace torchlight::collections

namespace torchlight {
template <class... Ts>
struct overload : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;
}  // namespace torchlight

#endif  // TORCHLIGHT_COLLECTIONS_COMMON_H
