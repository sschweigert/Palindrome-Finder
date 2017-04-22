#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

class Timer
{

	public:

		Timer();

		void start();

		float secondsElapsed() const;

	private:

		decltype(std::chrono::high_resolution_clock::now()) time;

};


#endif
