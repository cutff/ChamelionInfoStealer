cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Chamelion LANGUAGES CXX)
set(BIN_PATH "../")
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type" FORCE)
endif()
message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
add_library(ChamelionLibs
	STATIC
		../src/Chamelion/Headers/Includes.h
		../src/Chamelion/Headers/Browsers.h
		../src/Chamelion/Source/Browsers.cpp
		../src/Chamelion/Headers/Directories.h
		../src/Chamelion/Source/Directories.cpp
		../src/Chamelion/Headers/Logs.h
		../src/Chamelion/Source/Logs.cpp
		../src/Chamelion/Headers/Misc.h
		../src/Chamelion/Source/Misc.cpp
		../src/Chamelion/Headers/Process.h
		../src/Chamelion/Source/Process.cpp
		../src/Chamelion/Source/Registry.cpp
		../src/Chamelion/Headers/Registry.h
		../src/Chamelion/Headers/Timing.h
		../src/Chamelion/Source/Timing.cpp
		../src/Chamelion/Headers/Victim.h
		../src/Chamelion/Headers/VMEscape.h
		../src/Chamelion/Headers/NetUsers.h
		../src/Chamelion/Source/NetUsers.cpp
		../src/Chamelion/Headers/Printers.h
		../src/Chamelion/Source/Printers.cpp
		)
	
add_executable(Chamelion ../src/Chamelion/Source/Source.cpp)

target_link_libraries(Chamelion ChamelionLibs)
