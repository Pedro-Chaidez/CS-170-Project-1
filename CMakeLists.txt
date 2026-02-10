cmake_minimum_required(VERSION 3.15)
project(8PuzzleProject)

# Use C++ 20 as requested in your guide
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. COVERAGE FLAGS (Wrapped for Safety) ---
# We only apply these Linux/GCC flags if the compiler is GCC or Clang.
# This prevents errors if you are on Windows using MSVC.
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -lgcov")
endif()

# --- 2. OUTPUT DIRECTORY (From your guide) ---
# Ensures executables go into ./bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# --- 3. DEFINE SOURCES ---
# These are the logic files for the Game
set(CORE_SOURCES ./lib/Puzzle.cpp ./lib/Solver.cpp)

# --- 4. EXECUTABLE: THE MAIN GAME ---
# Compile main.cpp with the core logic
add_executable(main ./lib/main.cpp ${CORE_SOURCES})