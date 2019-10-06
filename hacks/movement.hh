///
///  ruvi base
///

// includes
#include "../core/interfaces/interfaces.hh"
#include "../sdk/utils/utilities.hh"

namespace features {

class movement { // using classes for this might be a little bit overkill, but
                 // IMO it's better for organization, and feature control.
public:
  void on_create_move(c_user_cmd *cmd); // calls every movement function
protected:
private:
  void bunny_hop(c_user_cmd *cmd);
  void auto_strafe(c_user_cmd *cmd);
};

} // namespace features

inline features::movement movement;