///
///  ruvi base
///

// includes
#include <array>
#include <cinttypes>
#include <cstdio>
#include <dlfcn.h>
#include <sstream>
#include <string>

/*

// handles
#include "_handles.hh"

#pragma once

inline void debug_handler() {  // I'm not to good with inline assembly,
                               // I'll boldly assume that this is right. - uber
  unsigned int _eax;
  unsigned int _ecx;
  unsigned int _ebp;
  unsigned int _esp;

  asm("movl _eax, %eax \n");
  asm("movl _ecx, %ecx \n");
  asm("movl _ebp, %ebp \n");
  asm("movl _esp, %esp \n");

  sprintf(__stream_buffer, "ERROR HANDLER:\neax: 0x%X\ecx: 0x%X\ebp: 0x%X\nesp:
0x%X", _eax, _ecx, _ebp, _esp);
}

*/

// macro handlers
#define CODE_START try {
#define CODE_END(str)                                                          \
  }                                                                            \
  catch (...) {                                                                \
    std::throw_with_nested(std::runtime_error(str));                           \
  }
#define EXCEPTION(str) std::throw_with_nested(std::runtime_error(str));