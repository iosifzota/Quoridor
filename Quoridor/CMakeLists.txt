cmake_minimum_required(VERSION 3.0)

project(quoridor)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set waring flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR
    ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  set(warnings "-Wall -Wextra -g")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  set(warnings "/W4 /EHsc")
endif()
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

# Executable
add_executable(${PROJECT_NAME} Main.cpp Piece.cpp)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR
   ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
   # link math-lib
   # target_link_libraries(${PROJECT_NAME} m)
endif()
