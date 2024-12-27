package;

import idl.Options;


class FuelCustomCode extends idl.CustomCode {
    public override function getHLInclude() {
		return "
        #ifdef _WIN32
#pragma warning(disable:4305)
#pragma warning(disable:4244)
#pragma warning(disable:4316)
#endif

        ";
	}

	public override function getJVMInclude() {
		return "";
	}

	public override function getEmscriptenInclude() {
		return "";
	}

	public override function getJSInclude() {
		return "";
	}

	public override function getHXCPPInclude() {
		return "
#ifndef INCLUDED_haxe_io_Bytes
#include <haxe/io/Bytes.h>
#endif

	inline ::String operator+(const ::String& lhs, uint32_t rhs) {
		return lhs + ::String((int)rhs);
	}
		
		inline ::haxe::io::Bytes convertStdBytesToHaxeIOBytes( const basisu::uint8_vec &bytes ) {
			::haxe::io::Bytes result = ::haxe::io::Bytes_obj::alloc(bytes.size());
			for (int i = 0; i < bytes.size(); i++) {
				result->b[i] = bytes[i];
			}
			return result;
		}

		inline ::haxe::io::Bytes getOutputKTX2DataAsBytes( basisu::basis_compressor *compressor ) {
			return convertStdBytesToHaxeIOBytes(compressor->get_output_ktx2_file());
		}
		inline ::haxe::io::Bytes getOutputBasisDataAsBytes( basisu::basis_compressor *compressor ) {
			return convertStdBytesToHaxeIOBytes(compressor->get_output_basis_file());
		}

		";
	}

}
class Generator {
	// Put any necessary includes in this string and they will be added to the generated files
	
	public static function main() {
        trace('Building...');
        var sampleCode : idl.CustomCode = new FuelCustomCode();
        var options = {
            idlFile: "jolt/jolt.idl",
            target: null,
            packageName: "jolt",
            nativeLib: "jolt",
            glueDir: null,
            autoGC: true,
            defaultConfig: "Release",
            architecture: ArchAll,
			hxDir:".",
            customCode: sampleCode,
			includes: ["jolt/jolt.h"], 
			libs:["jolt"]
        };

		new idl.Cmd(options).run();
	}
}
