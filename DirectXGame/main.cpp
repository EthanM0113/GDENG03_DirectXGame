#include <iostream>
#include "AppWindow.h"

using namespace std;

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
        cout << err.what();
        return -1;
    }

    return 0;
}