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

    if (data->table)
      collect_netvars(data->table->name, data->table);

    // debug purposes only
    m_dumped_tables++;

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

    // debug purposes only
    file << std::endl << "dumped: " + std::to_string(m_dumped_tables) + " tables" + ", " + std::to_string(m_dumped_netvars) + " netvars" << std::endl; 
  }
}

std::string netvars::dump_netvars(recv_table_t *table) {

  std::stringstream ss;

  // table name
  ss << std::endl << '[' << table->name << ']' << std::endl;

  for (std::size_t i = 0; i < table->num_props; i++) {

    recv_prop_t *current_netvar = &table->p_props[i];

    // remove useless stuff
    if (std::string("baseclass").compare(current_netvar->name) == 0)
      continue;

    // offset
    ss << current_netvar->name << " ="
       << " 0x" << std::uppercase << std::hex << current_netvar->offset
       << std::endl;

    // repeat
    if (current_netvar->data_table)
      dump_netvars(current_netvar->data_table);
  }

  // write to file
  return ss.str();
}

void netvars::collect_netvars(const std::string &table_name,
                              recv_table_t *table,
                              int table_offset) {

  // loop through tables and netvars
  for (std::size_t i = 0; i < table->num_props; ++i) {

    // current netvar
    recv_prop_t *current_netvar = &table->p_props[i];

    // current table
    recv_table_t *current_table = current_netvar->data_table;

    // if the table have at least one netvar store it
    if (current_table && current_table->num_props > 0)
      collect_netvars(table_name, current_table, current_netvar->offset);

    if (m_netvar[table_name][current_netvar->name] <= 0 &&
            (current_netvar->type == DPT_Float ||
        current_netvar->type == DPT_Int || current_netvar->type == DPT_String ||
        current_netvar->type == DPT_Vector ||
        current_netvar->type == DPT_VectorXY)) {

      // assign the offset of the netvar that we searched
      m_netvar[table_name][current_netvar->name] =
          static_cast<std::uintptr_t>(current_netvar->offset) + table_offset;

      // debug purposes only
      m_dumped_netvars++;
    }
  }
}