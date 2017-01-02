set(LIBNAME nescoretest)

# Add the tests
set(SRC
	TestMemory.h
	TestMemory.cpp
	CPUTest.h
	CPUGeneralTest.cpp
	CPUArithmeticTest.cpp
	CPUFlagTest.cpp
	CPUBranchingTest.cpp
	CPUIncreaseDecreaseTest.cpp
	CPULoadStoreTest.cpp
	CPUTransferTest.cpp
	CPUMiscellaneousTest.cpp
)

# Create the executable and link it.
add_executable(${LIBNAME} ${SRC})
target_link_libraries(${LIBNAME} nescore gtest gtest_main)

# Add the tests to CTest
add_test(${LIBNAME} ${LIBNAME})