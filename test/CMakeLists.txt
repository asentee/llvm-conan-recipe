cmake_minimum_required(VERSION 3.15)
project(test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED)
include(AddLLVM)
message(STATUS "Search path: ${CMAKE_MODULE_PATH}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_llvm_executable(test test.cpp)
llvm_map_components_to_libnames(llvm_libs core)
target_link_libraries(test PRIVATE ${llvm_libs})

if(LLVM_PROJECT_CLANG_ENABLED)
    target_link_libraries(test PRIVATE libclang)
endif()