//
//  ruvi base
//

#pragma once

// includes
#include <cstdint>
#include <cstdlib>
#include <link.h>
#include <memory.h>
#include <string.h>
#include <vector>

namespace memory {

std::uint8_t *find_pattern(const char *module, const char *signature);

template <unsigned int index, typename type, typename... arguments>
static type vfunc(void *thisptr, arguments... argument_list) {
  using fn = type (*)(void *, decltype(argument_list)...);
  return (*static_cast<fn **>(thisptr))[index](thisptr, argument_list...);
}

inline void **&get_vtable(void *instance, std::uintptr_t offset = 0x0) {
  return *reinterpret_cast<void ***>(std::uintptr_t(instance) + offset);
}

inline std::uintptr_t get_address(std::uintptr_t pointer, int offset,
                                  std::size_t size) {
  return pointer + *reinterpret_cast<std::uint32_t *>(pointer + offset) + size;
}
}; // namespace memory
