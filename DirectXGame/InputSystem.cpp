#include "InputSystem.h"
#include "AGameObject.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

InputSystem** InputSystem::getInstance()
{
}

void InputSystem::initialize()
{
}

void InputSystem::destroy()
{
}

void InputSystem::addListener(InputListener* listener)
{
	this->inputListenerList.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	// find object in use
	int index = -1;
	for(int i = 0; i < this->inputListenerList.size(); i++)
	{
		if(this->inputListenerList[i] == listener)
		{
			index = i;
			break;
		}

		if (index > -1)
		{
			this->inputListenerList.erase(this->inputListenerList.begin() + index);
		}
	}
}

void InputSystem::update()
{
	POINT currentPt = {};
	GetCursorPos(&currentPt);

	if(this->firstTimeCall)
	{
		this->firstTimeCall = false;
		this->oldMousePos = Point(currentPt.x, currentPt.y);
	}

	if(this->oldMousePos.getX() != currentPt.x
		|| this->oldMousePos.getY() != currentPt.y) 
	{
		Point deltaPt = Point(currentPt.x - this->oldMousePos.getX(),
			currentPt.y - this->oldMousePos.getY());
		this->callOnMouseMove(deltaPt);
	}

	this->oldMousePos = Point(currentPt.x, currentPt.y);

	if (GetKeyboardState(keyStates))
	{
		for(int i = 0; i < ARRAYSIZE(keyStates); i++)
		{
			if(this->keyStates[i] & 0x80 && this->keyStates[i] != this->oldKeyStates[i])
			{
				if(i == VK_LBUTTON && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - oldMousePos.getX(), currentPt.y - oldMousePos.getY());
					callOnLeftMouseDown(deltaPt);
				}
				else if(i == VK_RBUTTON && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - oldMousePos.getX(), currentPt.y - oldMousePos.getY());
					callOnRightMouseDown(deltaPt);
				}
				else
				{
					callOnKeyDown(i);
				}
			}
			else if (this->keyStates[i] != this->oldKeyStates[i])
			{
				if (i == VK_LBUTTON && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - oldMousePos.getX(), currentPt.y - oldMousePos.getY());
					callOnLeftMouseUp(deltaPt);
				}
				else if (i == VK_RBUTTON && this->keyStates[i] != this->oldKeyStates[i])
				{
					Point deltaPt = Point(currentPt.x - oldMousePos.getX(), currentPt.y - oldMousePos.getY());
					callOnRightMouseUp(deltaPt);
				}
				else
				{
					callOnKeyUp(i);
				}
			}
		}

		// store current keys to old states
		::memcpy(this->oldKeyStates, this->keyStates, sizeof(unsigned char) * 256);

	}
}

bool InputSystem::isKeyDown(int key)
{
	for (int i = 0; i < ARRAYSIZE(keyStates); i++)
	{
		if (this->keyStates[i] & 0x80 && i == key)
		{
			return true;
		}
		else if (i == key)
		{
			return false;
		}
	}

	return false;
}

bool InputSystem::isKeyUp(int key)
{
	for (int i = 0; i < ARRAYSIZE(keyStates); i++)
	{
		if (!(this->keyStates[i] & 0x80) && i == key)
		{
			return true;
		}
		else if (i == key)
		{
			return false;
		}
	}

	return false;
}

void InputSystem::callOnKeyDown(int key)
{
	for(int i = 0; i < this->inputListenerList.size(); i++)
	{
		this->inputListenerList[i]->onKeyDown(key);
	}

}

void InputSystem::callOnKeyUp(int key)
{
	for (int i = 0; i < this->inputListenerList.size(); i++)
	{
		this->inputListenerList[i]->onKeyUp(key);
	}
}

void InputSystem::callOnMouseMove(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++)
	{
		this->inputListenerList[i]->onMouseMove(deltaPt);
	}
}

void InputSystem::callOnLeftMouseDown(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++)
	{
		this->inputListenerList[i]->onLeftMouseDown(deltaPt);
	}
}

void InputSystem::callOnLeftMouseUp(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++)
	{
		this->inputListenerList[i]->onLeftMouseUp(deltaPt);
	}
}

void InputSystem::callOnRightMouseDown(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++)
	{
		this->inputListenerList[i]->onRightMouseDown(deltaPt);
	}
}

void InputSystem::callOnRightMouseUp(Point deltaPt)
{
	for (int i = 0; i < this->inputListenerList.size(); i++)
	{
		this->inputListenerList[i]->onRightMouseUp(deltaPt);
	}
}

