//
//  ruvi base
//

// includes
#include "netvars.hh"
#include "../../core/interfaces/interfaces.hh" // yikes :C

void netvars::on_entry_point() {

  c_client_class *client_class = csgo::base_client->get_all_classes();

  std::stringstream ss;

  // set this variable to true if you want to dump netvars
  constexpr bool DUMP_NETVARS = true;

  for (c_client_class *data = client_class; data != nullptr;
       data = data->next) {
    collect_netvars(data->table->name, data->table);

    if (DUMP_NETVARS)
      ss << netvars::dump_netvars(data->table);
  }

  if (DUMP_NETVARS) {

    // file name (located at game folder)
    std::ofstream file("netvars.txt");

    if (file.fail()) // todo: trow an exception here if it fails
      return;

    // read buffer and write to file
    file << ss.rdbuf();
  }
}

std::string netvars::dump_netvars(recv_table_t *table) {

  std::stringstream ss;

  // table name
  ss << '[' << table->name << ']' << std::endl;

  for (std::size_t i = 0; i < table->num_props; i++) {

    recv_prop_t *current_netvar = &table->p_props[i];

    // netvar name
    std::string_view netvar_name = current_netvar->name;

    // remove useless stuff
    if (netvar_name.find("baseclass") != std::string::npos ||
        netvar_name.find('0') != std::string::npos ||
        netvar_name.find('1') != std::string::npos ||
        netvar_name.find("2") != std::string::npos)
      continue;

    // offset
    ss << netvar_name << " ="
       << " 0x" << std::uppercase << std::hex << current_netvar->offset
       << std::endl;

    // repeat
    if (current_netvar->data_table)
      dump_netvars(current_netvar->data_table);
  }

  // write to file
  return ss.str();
}

void netvars::collect_netvars(std::string table_name, recv_table_t *table,
                              std::uintptr_t table_offset) {

  // loop through tables and netvars
  for (std::size_t i = 0; i < table->num_props; ++i) {

    // current netvar
    recv_prop_t *current_netvar = &table->p_props[i];

    // current table
    recv_table_t *current_table = current_netvar->data_table;

    // if we have at least one netvar on the table, store it
    if (current_table != nullptr && current_table->num_props > 0)
      collect_netvars(table_name, current_table, current_netvar->offset);

    // check if the netvar exists in the specified table
    if (m_netvar[table_name][current_netvar->name] <= 0) {

      // grab the offset of the netvar that we just searched
      m_netvar[table_name][current_netvar->name] =
          static_cast<std::uintptr_t>(current_netvar->offset) + table_offset;
    }
  }
}