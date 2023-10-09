#pragma once
#include <vector>
#include "InputListener.h"

using namespace std;

class InputSystem
{
public:
	static InputSystem* getInstance* ();
	static void initialize();
	static void destroy();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

	void update();

	// Global methods for checking key input status
	bool isKeyDown(int key);
	bool isKeyUp(int key);

private:
	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};
	InputSystem& operator=(InputSystem const&) {};

	// Keyboard helper methods
	void callOnKeyDown(int key);
	void callOnKeyUp(int key);

	void callOnMouseMove(Point deltaPt);
	void callOnLeftMouseDown(Point deltaPt);
	void callOnLeftMouseUp(Point deltaPt);
	void callOnRightMouseDown(Point deltaPt);
	void callOnRightMouseUp(Point deltaPt);

	static InputSystem* sharedInstance;
	vector<InputListener*> inputListenerList;
	unsigned char keyStates[256] = {};
	unsigned char oldKeyStates[256] = {};

	Point oldMousePos;
	bool firstTimeCall = true;

};

