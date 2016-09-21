cmake_minimum_required(VERSION 3.1.3)

# Variables to configure the build.
set(TESTS NO CACHE BOOL "Compile with unit tests (dependency on Google Test).")

# Set C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(TESTS)
	set(GTEST_ROOT "" CACHE PATH "Root to Google Test framework.")
	enable_testing()

	if(NOT GTEST_ROOT)
		message(FATAL_ERROR "You must set the path to a precompiled Google Test in GTEST_ROOT variable.")
	endif()
endif()

# Configure the project
project(nes)
add_subdirectory(nescore)