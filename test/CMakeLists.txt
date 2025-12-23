cmake_minimum_required(VERSION 3.15)
project(test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
# include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_llvm_executable(myTool test.cpp)
llvm_map_components_to_libnames(llvm_libs core)
target_link_libraries(myTool PRIVATE ${llvm_libs})