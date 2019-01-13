//
//  Ruvi - @special-parakeet.git
//

#pragma once

// includes
#include <cstdio>
#include <cstdint>

namespace memory {

	std::uint8_t* find_pattern( const char* module, const char* signature );

	inline void**&get_vtable( void* inst, size_t offset = 0 ) {
		return *reinterpret_cast<void***>(( size_t )inst + offset);
	}

	template<unsigned int index, typename type, typename ... arguments> static auto vfunc( void* thisptr, arguments ... argument_list ) -> type {
		using fn = type( * )( void*, decltype( argument_list )... );
		return ( *static_cast<fn**>(thisptr) )[ index ]( thisptr, argument_list... );
	}

	inline uintptr_t get_absolute_address( uintptr_t instruction_ptr, int offset, int size ) {
		return instruction_ptr + *reinterpret_cast<uint32_t*>(instruction_ptr + offset) + size;
	}
};
