package jolt;
#if hl

abstract BodyCreationSettings(idl.Types.Ref) from idl.Types.Ref to idl.Types.Ref {
	@:hlNative("jolt", "BodyCreationSettings_new0")
	static function new0():jolt.BodyCreationSettings return cast(0, BodyCreationSettings);
	public inline function new():jolt.BodyCreationSettings return new0();
	@:hlNative("jolt", "BodyCreationSettings_delete")
	public function delete():Void { }
}
abstract Config(idl.Types.Ref) from idl.Types.Ref to idl.Types.Ref {
	@:hlNative("jolt", "Config_new0")
	static function new0():jolt.Config return cast(0, Config);
	public inline function new():jolt.Config return new0();
	public var maxTempAllocatorSize(get, set) : Int;
	@:hlNative("jolt", "Config_get_maxTempAllocatorSize")
	function get_maxTempAllocatorSize():Int return 0;
	@:hlNative("jolt", "Config_set_maxTempAllocatorSize")
	function set_maxTempAllocatorSize(_v:Int):Int return 0;
	public var maxPhysicsJobs(get, set) : Int;
	@:hlNative("jolt", "Config_get_maxPhysicsJobs")
	function get_maxPhysicsJobs():Int return 0;
	@:hlNative("jolt", "Config_set_maxPhysicsJobs")
	function set_maxPhysicsJobs(_v:Int):Int return 0;
	public var maxPhysicsBarriers(get, set) : Int;
	@:hlNative("jolt", "Config_get_maxPhysicsBarriers")
	function get_maxPhysicsBarriers():Int return 0;
	@:hlNative("jolt", "Config_set_maxPhysicsBarriers")
	function set_maxPhysicsBarriers(_v:Int):Int return 0;
	public var maxThreads(get, set) : Int;
	@:hlNative("jolt", "Config_get_maxThreads")
	function get_maxThreads():Int return 0;
	@:hlNative("jolt", "Config_set_maxThreads")
	function set_maxThreads(_v:Int):Int return 0;
	public var maxBodies(get, set) : Int;
	@:hlNative("jolt", "Config_get_maxBodies")
	function get_maxBodies():Int return 0;
	@:hlNative("jolt", "Config_set_maxBodies")
	function set_maxBodies(_v:Int):Int return 0;
	public var numBodyMutexes(get, set) : Int;
	@:hlNative("jolt", "Config_get_numBodyMutexes")
	function get_numBodyMutexes():Int return 0;
	@:hlNative("jolt", "Config_set_numBodyMutexes")
	function set_numBodyMutexes(_v:Int):Int return 0;
	public var maxBodyPairs(get, set) : Int;
	@:hlNative("jolt", "Config_get_maxBodyPairs")
	function get_maxBodyPairs():Int return 0;
	@:hlNative("jolt", "Config_set_maxBodyPairs")
	function set_maxBodyPairs(_v:Int):Int return 0;
	public var maxContactConstraints(get, set) : Int;
	@:hlNative("jolt", "Config_get_maxContactConstraints")
	function get_maxContactConstraints():Int return 0;
	@:hlNative("jolt", "Config_set_maxContactConstraints")
	function set_maxContactConstraints(_v:Int):Int return 0;
	@:hlNative("jolt", "Config_delete")
	public function delete():Void { }
}
abstract Globals(idl.Types.Ref) from idl.Types.Ref to idl.Types.Ref {
	@:hlNative("jolt", "Globals_new1")
	static function new1(config:jolt.Config):jolt.Globals return cast(0, Globals);
	public inline function new(config:jolt.Config):jolt.Globals return new1(cast config);
	@:hlNative("jolt", "Globals_delete")
	public function delete():Void { }
}

#end
#if cpp

@:native("JPH::BodyCreationSettings") @:structAccess @:unreflective @:build(idl.macros.MacroTools.buildHXCPPIDLType("${JOLT_IDL_DIR}/jolt.idl")) extern class BodyCreationSettings {
	public function delete():Void;
	@:native("JPH::BodyCreationSettings")
	public static function make():BodyCreationSettings {
		return null;
	}
}
@:forward @:forwardStatics abstract BodyCreationSettingsPtr(cpp.Star<jolt.BodyCreationSettings>) from cpp.Star<jolt.BodyCreationSettings> to cpp.Star<jolt.BodyCreationSettings> {
	@:native("new JPH::BodyCreationSettings")
	public static function alloc():jolt.BodyCreationSettingsPtr return null;
	@:native("delete ")
	public function free():Void { }
}
@:native("hjolt::Config") @:structAccess @:unreflective @:build(idl.macros.MacroTools.buildHXCPPIDLType("${JOLT_IDL_DIR}/jolt.idl")) extern class Config {
	public var maxTempAllocatorSize : Int;
	public var maxPhysicsJobs : Int;
	public var maxPhysicsBarriers : Int;
	public var maxThreads : Int;
	public var maxBodies : Int;
	public var numBodyMutexes : Int;
	public var maxBodyPairs : Int;
	public var maxContactConstraints : Int;
	public function delete():Void;
	@:native("hjolt::Config")
	public static function make():Config {
		return null;
	}
}
@:forward @:forwardStatics abstract ConfigPtr(cpp.Star<jolt.Config>) from cpp.Star<jolt.Config> to cpp.Star<jolt.Config> {
	@:native("new hjolt::Config")
	public static function alloc():jolt.ConfigPtr return null;
	@:native("delete ")
	public function free():Void { }
}
@:native("hjolt::Globals") @:structAccess @:unreflective @:build(idl.macros.MacroTools.buildHXCPPIDLType("${JOLT_IDL_DIR}/jolt.idl")) extern class Globals {
	public function delete():Void;
	@:native("hjolt::Globals")
	public static function make(config:Config):Globals {
		return null;
	}
}
@:forward @:forwardStatics abstract GlobalsPtr(cpp.Star<jolt.Globals>) from cpp.Star<jolt.Globals> to cpp.Star<jolt.Globals> {
	@:native("new hjolt::Globals")
	public static function alloc(config:Config):jolt.GlobalsPtr return null;
	@:native("delete ")
	public function free():Void { }
}

#end
