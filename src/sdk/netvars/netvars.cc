//
//  ruvi base
//

// includes
#include "../../core/definitions/handler.hh"
#include "../../core/interfaces/interfaces.hh" // yikes :C
#include "netvars.hh"

void netvars::on_entry_point() {

  c_client_class *client_class = csgo::base_client->get_all_classes();

  static std::stringstream sn; // netvars
  static std::stringstream sc; // class id

  // set these variables to true if you want to dump netvars or class id
  constexpr bool DUMP_NETVARS  = true;
  constexpr bool DUMP_CLASS_ID = true;

  for (c_client_class *data = client_class; data != nullptr;
       data                 = data->next) {

    // populate the netvar container
    netvars::collect_netvars(data->table->name, data->table);

    if (DUMP_NETVARS) sn << netvars::dump_netvars(data->table);

    if (DUMP_CLASS_ID) sc << netvars::dump_class_id(data);
  }

  if (DUMP_NETVARS) {

    // file name (located at game folder)
    std::ofstream file(STR("netvars.dump"));

    if (file.fail()) EXCEPTION(STR("error handler - entry point - dumper"))

    // read buffer and write to file
    file << sn.rdbuf();
  }

  if (DUMP_CLASS_ID) {

    // file name (located at game folder)
    std::ofstream file(STR("classid.dump"));

    if (file.fail()) EXCEPTION(STR("error handler - entry point - dumper"))

    // read buffer and write to file
    file << sc.rdbuf();
  }
}

std::string netvars::dump_netvars(recv_table_t *table) {

  std::stringstream ss;

  // table name
  ss << std::endl << '[' << table->name << ']' << std::endl;

  for (std::size_t i = 0; i < table->num_props; i++) {

    recv_prop_t *current_netvar = &table->p_props[i];

    // remove useless stuff
    if (std::string(STR("baseclass")).compare(current_netvar->name) == 0)
      continue;

    // offset
    ss << current_netvar->name << STR(" =") << STR(" 0x") << std::uppercase
       << std::hex << current_netvar->offset << std::endl;

    // repeat
    if (current_netvar->data_table) dump_netvars(current_netvar->data_table);
  }

  return ss.str();
}

std::string netvars::dump_class_id(c_client_class *client_class) {

  std::stringstream ss;

  // class name (table)
  ss << client_class->network_name << STR(" = ") << client_class->class_id
     << std::endl;

  // todo: fix the class id always being 0

  return ss.str();
}

void netvars::collect_netvars(const std::string &table_name,
                              recv_table_t *     table,
                              std::uintptr_t     table_offset) {

  // loop through tables and netvars
  for (std::size_t i = 0; i < table->num_props; ++i) {

    // current netvar
    recv_prop_t *current_netvar = &table->p_props[i];

    // current table
    recv_table_t *current_table = current_netvar->data_table;

    // if the table have at least one netvar, store it
    if (current_table && current_table->num_props >= 1)
      netvars::collect_netvars(table_name, current_table,
                               current_netvar->offset);

    // assign an offset to the netvar
    m_netvar[table_name][current_netvar->name] =
        static_cast<std::uintptr_t>(current_netvar->offset + table_offset);
  }
}