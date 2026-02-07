cmake_minimum_required(VERSION 3.14)
project(8PuzzleSolver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output Directory Configuration
# This ensures executables go to the 'bin' folder relative to your build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(Headers Scripts)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# 1. Test executable
add_executable(
  unit_tests
  "Test scripts/UnitTests.cpp"
)

target_link_libraries(
  unit_tests
  GTest::gtest_main
)

# Discover tests for CTest
include(GoogleTest)
gtest_discover_tests(unit_tests)

# 2. Custom Target to force test execution
# This creates a "gatekeeper" task that runs the tests.
add_custom_target(run_unit_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS unit_tests
    COMMENT "Executing algorithm verification suite..."
)

# 3. Main Executable
add_executable(8PuzzleExecutable Scripts/8PuzzleAIAlgorithm.cpp)

# 4. ENFORCE TESTS
# By making the executable depend on the 'run_unit_tests' target, 
# 'make' will be forced to run (and pass) tests before it even 
# attempts to compile/link the main 8PuzzleExecutable.
add_dependencies(8PuzzleExecutable run_unit_tests)