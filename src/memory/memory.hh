//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <cstdio>
#include <cstdint>

namespace memory {

	std::uint8_t* find_pattern( const char* module, const char* signature );

	template<unsigned int index, typename type, typename ... arguments> static auto vfunc( void* thisptr, arguments ... argument_list ) -> type {
		using fn = type( * )( void*, decltype( argument_list )... );
		return ( *static_cast<fn**>(thisptr) )[ index ]( thisptr, argument_list... );
	}
};
