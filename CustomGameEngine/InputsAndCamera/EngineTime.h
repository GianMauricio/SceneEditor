#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

//This class is a glorified watch. It keeps track of the time between each frame update so that it can be used everywhere
//minimizing calculation time and also creating a more uniform time keeper in comparison to relying on time calculations
//locked to any one object

//TL;DR time keeper ex machina
class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();

private:
	//Singleton
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const&) {};

	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double delta_time = 0.0;

	static void LogFrameStart();
	static void LogFrameEnd();

	friend class Window;
};

