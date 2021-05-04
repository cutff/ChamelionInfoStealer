cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Chamelion LANGUAGES CXX)
set(BIN_PATH "../")
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type" FORCE)
endif()
message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
add_library(ChamelionLibs
	STATIC
		../src/Chamelion/Includes.h
		../src/Chamelion/Browsers.h
		../src/Chamelion/Browsers.cpp
		../src/Chamelion/Directories.h
		../src/Chamelion/Directories.cpp
		../src/Chamelion/Logs.h
		../src/Chamelion/Logs.cpp
		../src/Chamelion/Misc.h
		../src/Chamelion/Misc.cpp
		../src/Chamelion/Process.h
		../src/Chamelion/Process.cpp
		../src/Chamelion/Registry.cpp
		../src/Chamelion/Registry.h
		../src/Chamelion/Timing.h
		../src/Chamelion/Timing.cpp
		../src/Chamelion/Victim.h
		../src/Chamelion/VMEscape.h
		)
	
add_executable(Chamelion ../src/Chamelion/Source.cpp)

target_link_libraries(Chamelion ChamelionLibs)
