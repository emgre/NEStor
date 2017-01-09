set(LIBNAME nescoretest)

# Configure the path file
configure_file(
  "FilePaths.h.in"
  "${PROJECT_BINARY_DIR}/FilePaths.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# Add the tests
set(SRC
	TestMemory.h
	TestMemory.cpp
	CPUTest.h
	CPUGeneralTest.cpp
	CPUArithmeticTest.cpp
	CPUFlagTest.cpp
	CPUBranchingTest.cpp
	CPUJumpTest.cpp
	CPUIncreaseDecreaseTest.cpp
	CPULoadStoreTest.cpp
	CPUTransferTest.cpp
	CPUStackTest.cpp
	CPUMiscellaneousTest.cpp
	CPUTestSuite.cpp
)

# Create the executable and link it.
add_executable(${LIBNAME} ${SRC})
target_link_libraries(${LIBNAME} nescore gtest gtest_main)

# Add the tests to CTest
add_test(${LIBNAME} ${LIBNAME})