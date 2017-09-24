cmake_minimum_required(VERSION 3.2.2)
project(palindrome_generator)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

add_library(palindrome_generator
	src/palindrome_tools.cpp
	src/string_set.cpp
	src/subword_iterator.cpp
	src/superword_iterator.cpp
	src/word_building_stack.cpp
	src/timer.cpp
	src/entire_set_iterator.cpp
	src/palindrome_calculation.cpp
)

target_include_directories(palindrome_generator
	PUBLIC include)

add_executable(main src/main.cpp)

target_link_libraries(main
	palindrome_generator)


find_package(CxxTest)

if(CXXTEST_FOUND)
	include_directories(${CXXTEST_INCLUDE_DIR})
	enable_testing()
	CXXTEST_ADD_TEST(palindrome_unit_test unit_tests.cc
		${CMAKE_CURRENT_SOURCE_DIR}/unit_test/palindrome_tools_test.h
		${CMAKE_CURRENT_SOURCE_DIR}/unit_test/subword_iterator_test.h	
		${CMAKE_CURRENT_SOURCE_DIR}/unit_test/palindrome_calculation_test.h	
	)
	target_link_libraries(palindrome_unit_test palindrome_generator)
endif()
