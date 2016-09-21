set(LIBNAME nescoretest)

find_package(GTest REQUIRED)

# Add the tests
set(SRC
	CPUTest.cpp
)

# Create the executable and link it.
add_executable(${LIBNAME} ${SRC})
target_link_libraries(${LIBNAME} nescore GTest::GTest GTest::Main)

# Add the tests to CTest
GTEST_ADD_TESTS(${LIBNAME} "" AUTO)