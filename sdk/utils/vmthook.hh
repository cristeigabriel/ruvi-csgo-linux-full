//
//  ruvi base
//

#pragma once

// includes
#include <cassert>
#include <cstdint>
#include <cstring>

//
// credits to namaszo for that vmt class
//
class vmt_hook {
public:
  constexpr vmt_hook() : m_new_vmt{nullptr}, m_old_vmt{nullptr} {}

  ~vmt_hook() {

    if (m_new_vmt) delete[](m_new_vmt - 1);
  }

  void initialize(void **original_table) {
    m_old_vmt = original_table;

    std::size_t size = 0;
    while (m_old_vmt[size]) ++size;

    m_new_vmt = (new void *[size + 1]) + 1;
    std::memcpy(m_new_vmt - 1, m_old_vmt - 1, sizeof(void *) * (size + 1));
  }

  bool initialize_and_hook_instance(void *instance) {

    void **&vtbl        = *reinterpret_cast<void ***>(instance);
    bool    initialized = false;

    if (!m_old_vmt) {
      initialized = true;
      initialize(vtbl);
    }

    // hook instance
    hook_instance(instance);

    return initialized;
  }

  constexpr void leak_table() { m_new_vmt = nullptr; }

  void hook_instance(void *inst) const {
    void **&vtbl = *reinterpret_cast<void ***>(inst);
    assert(vtbl == m_old_vmt || vtbl == m_new_vmt);
    vtbl = m_new_vmt;
  }

  void unhook_instance(void *inst) const {
    void **&vtbl = *reinterpret_cast<void ***>(inst);
    assert(vtbl == m_old_vmt || vtbl == m_new_vmt);
    vtbl = m_old_vmt;
  }

  template <typename fn>
  fn hook_function(fn hooked_fn, const std::size_t index) {
    m_new_vmt[index] = reinterpret_cast<void *>(hooked_fn);
    return reinterpret_cast<fn>(m_old_vmt[index]);
  }

  template <typename fn>
  void apply_hook(std::size_t index) {
    fn::original = hook_function(&fn::hooked, index);
  }

  template <typename fn = std::uintptr_t>
  fn get_original_function(const int index) {
    return reinterpret_cast<fn>(m_old_vmt[index]);
  }

private:
  void **m_new_vmt = nullptr;
  void **m_old_vmt = nullptr;
};
