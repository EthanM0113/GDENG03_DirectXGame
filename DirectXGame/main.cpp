#include <iostream>
#include "AppWindow.h"

//using namespace std;

int main()
{
    AppWindow app;
    try {
        if (!app.init())
            return -1;

        while (app.isRunning())
        {
            app.broadcast();
        }

    }
    catch (const std::exception& err)
    {
	    std::cout << err.what();
        return -1;
    }

    app.onDestroy();

    return 0;
}