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
	return std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - time).count(); 

}
