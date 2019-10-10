///
///  ruvi base
///

#pragma once

// helpers
#define CODE_START try {
#define CODE_END(str)                                                          \
  }                                                                            \
  catch (...) {                                                                \
    std::throw_with_nested(std::runtime_error(str));                           \
  }
#define EXCEPTION(str) std::throw_with_nested(std::runtime_error(str));