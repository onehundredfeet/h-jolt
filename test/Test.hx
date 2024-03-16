package ;

typedef JoltSystem = jolt.Native.System;

class Test {
    public static function main() {
        JoltSystem.initialize();
        trace("Hello, World!"); 
        
    }
}