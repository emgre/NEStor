set(LIBNAME nescoretest)

# Add the tests
set(SRC
	CPUTest.cpp
)

# Create the executable and link it.
add_executable(${LIBNAME} ${SRC})
target_link_libraries(${LIBNAME} nescore gtest gtest_main)

# Add the tests to CTest
add_test(${LIBNAME} ${LIBNAME})