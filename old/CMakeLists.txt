cmake_minimum_required(VERSION 3.10)

if (NOT PATH_TO_IDL) 
set(PATH_TO_IDL "ext/hl-idl")
endif()


include(${PATH_TO_IDL}/h-idl-preamble.cmake)

#you need to modify this yourself
project(jolt)



# a bunch of pre-configured options that may or may not be useful
# it attempts to cover most of what is used for basic libraries
# you can reference the paths defined here to help make your cmake code more portable
include(${PATH_TO_IDL}/h-idl-defines.cmake)


set( PROJECT_ADDITIONAL_SOURCES 
)

set (PROJECT_ADDITIONAL_INCLUDES
"${CMAKE_CURRENT_SOURCE_DIR}/ext/jolt"
)



if (APPLE)
set(PLAT_DIR "osx")
elseif(WIN32)
set(PLAT_DIR "win64")
elseif(UNIX)
set( PLAT_DIR "linux64")
endif()


set (PROJECT_ADDITIONAL_LIB_DIRS
#"build/jolt"
)


set(PROJECT_ADDITIONAL_LIBS
"${CMAKE_CURRENT_SOURCE_DIR}/build_jolt/libJolt.a"
)


include(${PATH_TO_IDL}/h-idl-configure.cmake)


