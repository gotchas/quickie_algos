cmake_minimum_required(VERSION 3.17.0)

INCLUDE( SetupHunter.cmake )
project(quickie_algos VERSION 0.1.0)

#set(CMAKE_VERBOSE_MAKEFILE ON) # ? interferes with errors diagnostic - jump to an error in editor

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) ## on g++ this ensures: -std=c++20 and not -std=gnu++20

include_directories(.)

find_package(GTest CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

add_executable(bench benchmark.cpp)
target_link_libraries(bench benchmark::benchmark)

### ### ### ### ### ### ### TESTS
include(CTest)
enable_testing()


add_executable(test_graph test/test_graph.cpp)
target_link_libraries(test_graph PRIVATE GTest::gmock_main)
add_test(graph test_graph)

add_executable(test_topo_s.exe test/test_topo_sort.cpp)
add_test(topo_sort test_topo_s.exe)

add_executable(test_sort test/test_sorting.cpp)
add_test(sort test_sort)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
