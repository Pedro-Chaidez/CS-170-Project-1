cmake_minimum_required(VERSION 3.14)
project(8PuzzleSolver)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(Headers)

# Add the main executable
add_executable(8PuzzlesExcecutable Scripts/8PuzzleAIAlgorithm.c++)

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

# Add test executable
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