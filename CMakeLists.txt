cmake_minimum_required(VERSION 3.14)
project(8PuzzleSolver)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Output Directory Configuration
# This puts all compiled executables (.exe) into a 'bin' folder 
# inside your build directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(Headers)

# 2. Main Executable
# Changed name to '8PuzzleExecutable' (fixed typo) 
# and updated source to 'main.c++'
# Note: If main.c++ is inside the 'Scripts' folder, use: Scripts/main.c++
add_executable(8PuzzleExecutable Scripts/8PuzzleAIAlgorithm.cpp)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# 3. Test executable
# This will also be placed in the 'bin' folder automatically
add_executable(
  unit_tests
  "Test scripts/UnitTests.c++"
)

# Link test executable with Google Test
target_link_libraries(
  unit_tests
  GTest::gtest_main
)

# Include Google Test's test discovery
include(GoogleTest)
gtest_discover_tests(unit_tests)