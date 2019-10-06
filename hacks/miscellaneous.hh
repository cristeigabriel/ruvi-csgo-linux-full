///
///  ruvi base
///

// includes
#include "../core/interfaces/interfaces.hh"
#include "../sdk/utils/utilities.hh"

namespace features {

class miscellaneous { // using classes for this might be a little bit overkill, but
                 // IMO it's better for organization, and feature control.
public:
  void on_create_move(c_user_cmd *cmd); // calls every miscellaneous function
protected:
private:
  void rank_revealer(c_user_cmd *cmd);
};

} // namespace features

inline features::miscellaneous miscellaneous;