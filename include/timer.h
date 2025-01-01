#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

template <class Func>
float timeFunction(Func func)
{
	auto start = std::chrono::high_resolution_clock::now();

	func();

	auto currentTime = std::chrono::high_resolution_clock::now();
	auto numNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - start).count();
	return numNanoseconds / 1e9; 
}


#endif
