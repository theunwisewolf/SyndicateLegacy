#ifndef TIMER_H_
#define TIMER_H_

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace Venus { namespace Utilities { 

class Timer
{
private:

#if defined(WIN32) || defined(_WIN32)
	LARGE_INTEGER m_Start;
	LARGE_INTEGER m_Frequency;
#else
	timeval m_Start;
#endif

public:
	Timer();
	void Reset();

	// Evaluates elapsed time in microsecond precision
	double Elapsed();

	// Returns elapsed time in seconds
	double getElapsedTime();

	// Returns elapsed time in seconds
	double getElapsedTimeInSec();

	// Returns elapsed time in microseconds
	double getElapsedTimeInMicroSec();

	// Returns elapsed time in milliseconds
	double getElapsedTimeInMilliSec();

	~Timer();
};

} }

#endif