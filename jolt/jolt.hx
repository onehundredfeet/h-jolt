package jolt;
#if hl

abstract BodyCreationSettings(idl.Types.Ref) from idl.Types.Ref to idl.Types.Ref {
	@:hlNative("jolt", "BodyCreationSettings_new0")
	static function new0():jolt.BodyCreationSettings return cast(0, BodyCreationSettings);
	public inline function new():jolt.BodyCreationSettings return new0();
	@:hlNative("jolt", "BodyCreationSettings_delete")
	public function delete():Void { }
}
abstract JoltConfig(idl.Types.Ref) from idl.Types.Ref to idl.Types.Ref {
	@:hlNative("jolt", "JoltConfig_new0")
	static function new0():jolt.JoltConfig return cast(0, JoltConfig);
	public inline function new():jolt.JoltConfig return new0();
	public var maxTempAllocatorSize(get, set) : Int;
	@:hlNative("jolt", "JoltConfig_get_maxTempAllocatorSize")
	function get_maxTempAllocatorSize():Int return 0;
	@:hlNative("jolt", "JoltConfig_set_maxTempAllocatorSize")
	function set_maxTempAllocatorSize(_v:Int):Int return 0;
	public var maxPhysicsJobs(get, set) : Int;
	@:hlNative("jolt", "JoltConfig_get_maxPhysicsJobs")
	function get_maxPhysicsJobs():Int return 0;
	@:hlNative("jolt", "JoltConfig_set_maxPhysicsJobs")
	function set_maxPhysicsJobs(_v:Int):Int return 0;
	public var maxPhysicsBarriers(get, set) : Int;
	@:hlNative("jolt", "JoltConfig_get_maxPhysicsBarriers")
	function get_maxPhysicsBarriers():Int return 0;
	@:hlNative("jolt", "JoltConfig_set_maxPhysicsBarriers")
	function set_maxPhysicsBarriers(_v:Int):Int return 0;
	public var maxThreads(get, set) : Int;
	@:hlNative("jolt", "JoltConfig_get_maxThreads")
	function get_maxThreads():Int return 0;
	@:hlNative("jolt", "JoltConfig_set_maxThreads")
	function set_maxThreads(_v:Int):Int return 0;
	public var maxBodies(get, set) : Int;
	@:hlNative("jolt", "JoltConfig_get_maxBodies")
	function get_maxBodies():Int return 0;
	@:hlNative("jolt", "JoltConfig_set_maxBodies")
	function set_maxBodies(_v:Int):Int return 0;
	public var numBodyMutexes(get, set) : Int;
	@:hlNative("jolt", "JoltConfig_get_numBodyMutexes")
	function get_numBodyMutexes():Int return 0;
	@:hlNative("jolt", "JoltConfig_set_numBodyMutexes")
	function set_numBodyMutexes(_v:Int):Int return 0;
	public var maxBodyPairs(get, set) : Int;
	@:hlNative("jolt", "JoltConfig_get_maxBodyPairs")
	function get_maxBodyPairs():Int return 0;
	@:hlNative("jolt", "JoltConfig_set_maxBodyPairs")
	function set_maxBodyPairs(_v:Int):Int return 0;
	public var maxContactConstraints(get, set) : Int;
	@:hlNative("jolt", "JoltConfig_get_maxContactConstraints")
	function get_maxContactConstraints():Int return 0;
	@:hlNative("jolt", "JoltConfig_set_maxContactConstraints")
	function set_maxContactConstraints(_v:Int):Int return 0;
	@:hlNative("jolt", "JoltConfig_delete")
	public function delete():Void { }
}
abstract JoltSystem(idl.Types.Ref) from idl.Types.Ref to idl.Types.Ref {
	@:hlNative("jolt", "JoltSystem_delete")
	public function delete():Void { }
}
abstract JoltGlobals(idl.Types.Ref) from idl.Types.Ref to idl.Types.Ref {
	@:hlNative("jolt", "JoltGlobals_new1")
	static function new1(config:JoltConfig):jolt.JoltGlobals return cast(0, JoltGlobals);
	public inline function new(config:JoltConfig):jolt.JoltGlobals return new1(cast config);
	@:hlNative("jolt", "JoltGlobals_createSystem0")
	public function createSystem():JoltSystem return null;
	@:hlNative("jolt", "JoltGlobals_updateSystem3")
	public function updateSystem(system:JoltSystem, deltaTime:Single, collisionSubSteps:Int):Void { }
	@:hlNative("jolt", "JoltGlobals_delete")
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
@:native("hjolt::Config") @:structAccess @:unreflective @:build(idl.macros.MacroTools.buildHXCPPIDLType("${JOLT_IDL_DIR}/jolt.idl")) extern class JoltConfig {
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
	public static function make():JoltConfig {
		return null;
	}
}
@:forward @:forwardStatics abstract JoltConfigPtr(cpp.Star<jolt.JoltConfig>) from cpp.Star<jolt.JoltConfig> to cpp.Star<jolt.JoltConfig> {
	@:native("new hjolt::Config")
	public static function alloc():jolt.JoltConfigPtr return null;
	@:native("delete ")
	public function free():Void { }
}
@:native("hjolt::PhysicsSystemWrapper") @:structAccess @:unreflective @:build(idl.macros.MacroTools.buildHXCPPIDLType("${JOLT_IDL_DIR}/jolt.idl")) extern class JoltSystem {
	public function delete():Void;
}
@:forward @:forwardStatics abstract JoltSystemPtr(cpp.Star<jolt.JoltSystem>) from cpp.Star<jolt.JoltSystem> to cpp.Star<jolt.JoltSystem> {

}
@:native("hjolt::Globals") @:structAccess @:unreflective @:build(idl.macros.MacroTools.buildHXCPPIDLType("${JOLT_IDL_DIR}/jolt.idl")) extern class JoltGlobals {
	public function createSystem():JoltSystemPtr;
	public function updateSystem(system:JoltSystemPtr, deltaTime:Single, collisionSubSteps:Int):Void;
	public function delete():Void;
	@:native("hjolt::Globals")
	public static function make(config:JoltConfigPtr):JoltGlobals {
		return null;
	}
}
@:forward @:forwardStatics abstract JoltGlobalsPtr(cpp.Star<jolt.JoltGlobals>) from cpp.Star<jolt.JoltGlobals> to cpp.Star<jolt.JoltGlobals> {
	@:native("new hjolt::Globals")
	public static function alloc(config:JoltConfigPtr):jolt.JoltGlobalsPtr return null;
	@:native("delete ")
	public function free():Void { }
}

#end
