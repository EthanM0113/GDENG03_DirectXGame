#include "EngineBackend.h"
#include <cstddef>

EngineBackend* EngineBackend::sharedInstance = NULL;

EngineBackend* EngineBackend::getInstance()
{
	return sharedInstance;
}

void EngineBackend::initialize()
{
	sharedInstance = new EngineBackend();
}

void EngineBackend::destroy()
{
	delete sharedInstance;
}

void EngineBackend::setMode(EditorMode mode)
{
	this->editorMode = mode;
}

void EngineBackend::startFrameStep()
{
	frameStepping = true;
}

void EngineBackend::endFrameStep()
{
	frameStepping = false;
}

bool EngineBackend::insideFrameStep()
{
	return frameStepping;
}

EngineBackend::EditorMode EngineBackend::getMode()
{
	return this->editorMode;
}

EngineBackend::EngineBackend()
{
}

EngineBackend::~EngineBackend()
{
}
