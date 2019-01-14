//
//  Ruvi - @ruvi-framework.git
//

// includes
#include "memory.hh"
#include <vector>
#include <memory>
#include <unordered_map>
#include <link.h>
#include <string.h>

// structs
struct s_dlinfo {

	const char* library = nullptr;
	uintptr_t address = 0;
	size_t size = 0;
};

// declarations
std::vector<s_dlinfo> libraries;

inline bool compare( const unsigned char* pData, const unsigned char* bMask, const char* szMask ) {

	for ( ; *szMask; ++szMask, ++pData, ++bMask ) {

		if ( *szMask == 'x' && *pData != *bMask ) {
			return false;
		}
	}

	return ( *szMask ) == 0;
}

bool get_library_info( const char* library, uintptr_t* address, size_t* size ) {

	if ( libraries.size( ) == 0 ) {

		dl_iterate_phdr( [ ]( struct dl_phdr_info* info, size_t, void* ) {

			s_dlinfo library_info = { };

			library_info.library = info->dlpi_name;
			library_info.address = info->dlpi_addr + info->dlpi_phdr[ 0 ].p_vaddr;
			library_info.size = info->dlpi_phdr[ 0 ].p_memsz;

			libraries.push_back( library_info );

			return 0;
		}, nullptr
		);
	}

	for ( const s_dlinfo &current: libraries ) {

		if ( !strcasestr( current.library, library ) )
			continue;

		if ( address )
			*address = current.address;

		if ( size )
			*size = current.size;

		return true;
	}

	return false;
}


std::uint8_t* memory::find_pattern( const char* module, const char* signature ) {


	static auto pattern_to_byte = [ ]( const char* pattern ) {

		auto bytes = std::vector<int> { };
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen( pattern );

		for ( auto current = start; current < end; ++current ) {

			if ( *current == '?' ) {
				++current;

				if ( *current == '?' ) {
					++current;
				}

				bytes.push_back( -1 );
			}
			else {
				bytes.push_back( strtoul( current, &current, 16 ) );
			}
		}

		return bytes;
	};

	uintptr_t moduleptr = 0;
	size_t sizeOfImage = 0;

	get_library_info( module, &moduleptr, &sizeOfImage );

	auto patternBytes = pattern_to_byte( signature );
	auto scanBytes = reinterpret_cast<std::uint8_t*>(moduleptr);

	auto s = patternBytes.size( );
	auto d = patternBytes.data( );

	for ( auto i = 0ul; i < sizeOfImage - s; ++i ) {

		bool found = true;

		for ( auto j = 0ul; j < s; ++j ) {
			if ( scanBytes[ i + j ] != d[ j ] && d[ j ] != -1 ) {
				found = false;
				break;
			}
		}

		if ( found ) {
			return &scanBytes[ i ];
		}
	}

	return nullptr;
}
