#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

//! \brief Wrapper for chrono stdlib that makes timing of execution easy.
class Timer
{

	public:

		//! \brief Create and start a timer
		Timer();

		//! \brief Reset a timer's start to begin timing a process
		void start();

		//! \brief Obtain the time elapsed since Timer was constructed or the
		//! last time start() was called, whichever is less
		float secondsElapsed() const;

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> time;

};


#endif
