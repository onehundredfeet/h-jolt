#!/bin/bash
haxe --library hl-idl --class-path generator --run Generator generate --target hxcpp --hx --builder Ninja --idl ../../hl-idl --config Release 

