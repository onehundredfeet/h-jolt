package jolt;


typedef Native = haxe.macro.MacroType<[
	idl.Module.build({
		idlFile: "jolt.idl",
		target: #if hl "hl" #elseif (java || jvm) "jvm" #else "Unsupported target host" #end,
		packageName: "jolt",
		autoGC: true,
		nativeLib: "jolt"
	})
]>;

