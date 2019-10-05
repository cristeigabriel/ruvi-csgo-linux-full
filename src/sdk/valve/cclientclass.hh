//
//  ruvi base
//

#pragma once

// includes
#include "crecvproxydata.hh"

class i_client_networkable;

typedef i_client_networkable *(*create_client_class_fn)(int entity_num,
                                                        int serial_num);
typedef i_client_networkable *(*create_event_fn)();

class c_client_class {
public:
  create_client_class_fn create_client;
  create_event_fn *      create_event;
  char *                 network_name;
  recv_table_t *         table;
  c_client_class *       next;
  int                    class_id;
};