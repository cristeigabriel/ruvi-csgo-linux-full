//
//  ruvi base
//

#pragma once

// includes
#include "../valve/crecvproxydata.hh"
#include <string>
#include <fstream>
#include <unordered_map>

// macros
#define NETVAR(type, function_name, table_name, netvar_name)                   \
  type function_name() {                                                       \
    static std::uintptr_t offset = netvars::m_netvar[table_name][netvar_name]; \
    return *reinterpret_cast<type *>(std::uintptr_t(this) + offset);           \
  };

#define OFFSET(type, function_name, offset)                                    \
  type function_name() {                                                       \
    return *reinterpret_cast<type *>(std::uintptr_t(this) + offset);           \
  };

#define OFFSET_PTR(type, function_name, offset)                                \
  type *function_name() {                                                      \
    return reinterpret_cast<type *>(std::uintptr_t(this) + offset);            \
  };

namespace netvars {

// netvar container
inline std::unordered_map<std::string,
                          std::unordered_map<std::string, std::uintptr_t>>
    m_netvar;

void on_entry_point();
void collect_netvars(std::string table_name, recv_table_t *table,
                     std::uintptr_t table_offset = 0x0);
std::string dump_netvars(recv_table_t *table);
} // namespace netvars