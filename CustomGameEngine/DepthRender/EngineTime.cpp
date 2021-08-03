#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::initialize()
{
	sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
	return sharedInstance->delta_time;
}

EngineTime::EngineTime()
{
}


EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_sec = sharedInstance->end - sharedInstance->start;

	sharedInstance->delta_time = elapsed_sec.count();

	//std::cout << "Frame finished in " << sharedInstance->delta_time << " seconds" << std::endl;
}
