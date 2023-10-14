#pragma once
#include <iostream>
#include <unordered_set>

#include "InputListener.h"
#include <Windows.h>
#include <vector>

#include "Point.h"

using namespace std;

class InputSystem
{

public:
	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void update();

	// Global methods for checking key input status
	bool isKeyDown(int key);
	bool isKeyUp(int key);
	void setCursorPosition(const Point& pos);

private:
	static InputSystem* sharedInstance;

	// Keyboard helper methods
	void callOnKeyDown(int key);
	void callOnKeyUp(int key);

	// Mouse helper methods
	void callOnMouseMove(Point deltaPt);
	void callOnLeftMouseDown(Point deltaPt);
	void callOnLeftMouseUp(Point deltaPt);
	void callOnRightMouseDown(Point deltaPt);
	void callOnRightMouseUp(Point deltaPt);

	vector<InputListener*> inputListenerList;
	// keyboard data
	unordered_set<InputListener*> m_set_listeners;
	unsigned char keyStates[256] = {};
	unsigned char oldKeyStates[256] = {};
	// mouse data
	Point oldMousePos;
	bool firstTimeCall = true;

	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};             // copy constructor is private. You can also do `... = delete`
	InputSystem& operator=(InputSystem const&) {};  // assignment operator is private. You can also do `... = delete`
};