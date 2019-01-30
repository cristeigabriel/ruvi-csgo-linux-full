//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include "utils/vmthook.hh"
#include "interfaces/interfaces.hh"

namespace hooks {

    void on_entry_point();

    struct paint {
        typedef void( fn)( void*, e_paint_mode );
        static fn hooked;
        static fn* original;
    };

    struct paint_traverse {
        typedef void( fn)( void*, unsigned long long, bool, bool );
        static fn hooked;
        static fn* original;
    };

    struct set_key_code_state {
        typedef void( fn)( void*, e_button_code, bool );
        static fn hooked;
        static fn* original;
    };
}