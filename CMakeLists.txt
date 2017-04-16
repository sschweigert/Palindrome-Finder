cmake_minimum_required(VERSION 3.2.2)
project(programming_test)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

add_library(programming_test
	src/palindrome_tools.cpp
	src/string_set.cpp
	src/subword_iterator.cpp
	src/superword_iterator.cpp
)

target_include_directories(programming_test
	PUBLIC include)

add_executable(main src/main.cpp)

target_link_libraries(main
	programming_test)

