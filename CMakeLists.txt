cmake_minimum_required(VERSION 3.1.3)

# Configure the project
project(nestor)

# Variables to configure the build
set(TESTS YES CACHE BOOL "Compile with unit tests.")

# Set C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Used by VS Code to enable debugging
include(CMakeToolsHelpers OPTIONAL)

if(TESTS)
	include(CTest)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	add_subdirectory(external/googletest)
endif()

# Add subdirectories
add_subdirectory(nescore)