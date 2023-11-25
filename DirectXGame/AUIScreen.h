#pragma once
#include <string>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

typedef std::string String;
class UIManager;

class AUIScreen
{
protected:
	typedef std::string String;

	AUIScreen(String name);
	~AUIScreen();

	void setEnabled(bool flag);

	String getName();
	bool getEnabled();
	virtual void drawUI(void* shaderByteCode, size_t sizeShader) = 0;

	String name;
	bool isEnabled;

	friend class UIManager;
};

