//
//  ruvi base
//

// includes
#include "../memory/memory.hh"
#include "../vector/vector.hh"

class c_client_class;

class i_client_networkable {
public:
  virtual ~i_client_networkable(){};

  void release() { return memory::vfunc<1, void>(this); }

  c_client_class *get_client_class() {
    return memory::vfunc<2, c_client_class *>(this);
  }

  bool is_dormant() { return memory::vfunc<9, bool>(this); }

  int get_index() { return memory::vfunc<10, int>(this); }

  void set_destroyed_on_recreate_entities() {
    return memory::vfunc<13, void>(this);
  }
};