#pragma once

#include <chrono>

using namespace std::chrono;

class Timer
{
public:
	Timer()
	{
		tpStart = high_resolution_clock::now();
	}

	~Timer()
	{

	}

	void start()
	{
		tpStart = high_resolution_clock::now();
	}

	Timer& stop()
	{
		tpEnd = high_resolution_clock::now();
		return *this;
	}

	long long toNanoS()
	{
		return duration_cast<nanoseconds>(tpEnd - tpStart).count();
	}

	long long toMilliS()
	{
		return duration_cast<milliseconds>(tpEnd - tpStart).count();
	}

	long long toMicroS()
	{
		return duration_cast<microseconds>(tpEnd - tpStart).count();
	}

	long long toS()
	{
		return duration_cast<seconds>(tpEnd - tpStart).count();
	}



private:
	steady_clock::time_point tpStart;
	steady_clock::time_point tpEnd;
};

