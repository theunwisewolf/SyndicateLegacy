#include "Timer.h"

namespace Syndicate { namespace Utilities { 

Timer::Timer()
{
#if defined(WIN32) || defined(_WIN32)
	QueryPerformanceFrequency(&this->m_Frequency);
	QueryPerformanceCounter(&this->m_Start);
#else
	gettimeofday(&this->m_Start, NULL);
#endif
}

void Timer::Reset()
{
#if defined(WIN32) || defined(_WIN32)
	QueryPerformanceCounter(&this->m_Start);
#else
	gettimeofday(&this->m_Start, NULL);
#endif
}

double Timer::Elapsed()
{
#if defined(WIN32) || defined(_WIN32)
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);

	return ( (current.QuadPart - this->m_Start.QuadPart) * 1000000.0f ) / this->m_Frequency.QuadPart;
#else
	timeval current;
	gettimeofday(&this->current, NULL);

	return (current.tv_sec - this->m_Start.tv_sec) * 1000000.0f + ( current.tv_usec - this->m_Start.tv_usec );
#endif
}

double Timer::getElapsedTime()
{
	return this->getElapsedTimeInSec();
}

double Timer::getElapsedTimeInMicroSec()
{
	return this->Elapsed();
}

double Timer::getElapsedTimeInMilliSec()
{
	return this->Elapsed() * 0.001;
}

double Timer::getElapsedTimeInSec()
{
	return this->Elapsed() * 0.000001;
}

Timer::~Timer()
{
}

}}