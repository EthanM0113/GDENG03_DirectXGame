#include "AUIScreen.h"

AUIScreen::AUIScreen(String name)
{
	this->name = name;
	isEnabled = true;
}

AUIScreen::~AUIScreen()
{
}

void AUIScreen::setEnabled(bool flag)
{
	isEnabled = flag;
}

String AUIScreen::getName()
{
	return name;
}

bool AUIScreen::getEnabled()
{
	return isEnabled;
}
