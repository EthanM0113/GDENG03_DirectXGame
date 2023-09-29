#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance;

EngineTime::EngineTime()
{
	
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	EngineTime::sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	EngineTime::sharedInstance->end = EngineTime::sharedInstance->start;
}

void EngineTime::initialize()
{
	EngineTime* orignalInstance = new EngineTime();
	EngineTime::sharedInstance = orignalInstance;
	EngineTime::sharedInstance->end = std::chrono::system_clock::now();
	EngineTime::sharedInstance->start = std::chrono::system_clock::now();
}

double EngineTime::getDeltaTime()
{
	std::chrono::duration<double> elapsed_seconds = EngineTime::sharedInstance->start - EngineTime::sharedInstance->end;
	EngineTime::sharedInstance->deltaTime = elapsed_seconds.count();

	return EngineTime::sharedInstance->deltaTime;


}
