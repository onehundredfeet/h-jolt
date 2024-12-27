package;

import idl.Options;

class Build extends idl.BuildBase {
	// Put any necessary includes in this string and they will be added to the generated files
	inline static final packageName = "jolt";

	var options = {
		idlFile: 'lib/${packageName}.idl',
		target: null,
		packageName: '${packageName}',
		nativeLib: '${packageName}',
		outputDir: "src",
		includeCode: null,
		autoGC: true,
		defaultConfig: "Release",
		architecture: ArchAll
	};

	function new() {
		super(options);
	}

	override function getJVMInclude()
		return "";

	override function getHLInclude()
		return "
#ifdef _WIN32
#pragma warning(disable:4305)
#pragma warning(disable:4244)
#pragma warning(disable:4316)
#endif
#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

JPH_SUPPRESS_WARNINGS

#include \"h-jolt.h\"
";

	public static function main() {
		var b = new Build();

		b.parseArgs();
	}
}
