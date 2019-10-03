//
//  ruvi base
//

#pragma once

// includes
#include "../memory/memory.hh"

class i_client_entity_list {
public:
  virtual void *get_client_networkable(int entindex) = 0;
  virtual void *get_client_networkable_from_handle(void *handle) = 0;
  virtual void *get_client_unknown_from_handle(void *handle) = 0;
  virtual void *get_client_entity(int entindex) = 0;
  virtual void *get_client_entity_from_handle(void *handle) = 0;
  virtual int number_of_entities(bool include_non_networkable) = 0;
  virtual int get_highest_entity_index() = 0;
  virtual void set_max_entities(int max_entities) = 0;
  virtual int get_max_entities() = 0;
};