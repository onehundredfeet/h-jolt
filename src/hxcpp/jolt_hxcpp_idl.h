#pragma once
#include "jolt/jolt.h"
#include "h-jolt.h"


// #ifndef INCLUDED_haxe_io_Bytes
// #include <haxe/io/Bytes.h>
// #endif

	inline ::String operator+(const ::String& lhs, uint32_t rhs) {
		return lhs + ::String((int)rhs);
	}
		
		// inline ::haxe::io::Bytes convertStdBytesToHaxeIOBytes( const basisu::uint8_vec &bytes ) {
		// 	::haxe::io::Bytes result = ::haxe::io::Bytes_obj::alloc(bytes.size());
		// 	for (int i = 0; i < bytes.size(); i++) {
		// 		result->b[i] = bytes[i];
		// 	}
		// 	return result;
		// }

		