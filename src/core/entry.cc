//
//  Ruvi - @special-parakeet.git
//

// includes
#include <thread>
#include "hooks/hooks.hh"
#include "utils/rendering.hh"
#include "interfaces/interfaces.hh"

// lets initialize all our stuff here
void install() {

    while ( !dlopen( "./bin/linux64/serverbrowser_client.so", RTLD_NOLOAD | RTLD_NOW ) )
        std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

    interfaces::on_entry_point();
    draw::on_entry_point();
    hooks::on_entry_point();

}

// entry point
int __attribute__((constructor)) startup( ) {

    std::thread main_thread( install );
    main_thread.detach( );

    return 0;
}
