cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(GoogleBenchmark REQUIRED)



include_directories(${benchmark_INCLUDE_DIRS})


add_executable(palindrome palindrome/palindrome.cpp)
add_executable(find_odd find_odd/find_odd.cpp)

target_link_libraries(find_odd
        ${benchmark_LIBRARIES}
        tbb pthread)

target_link_libraries(palindrome ${benchmark_LIBRARIES} pthread)
if ("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    target_link_libraries(palindrome Shlwapi)
endif()