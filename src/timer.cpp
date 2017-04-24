#include <timer.h>

Timer::Timer() 
{
	start();
}

void Timer::start()
{
	time = std::chrono::high_resolution_clock::now();
}

float Timer::secondsElapsed() const
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto numNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - time).count();
	return numNanoseconds / 1e9; 

}
