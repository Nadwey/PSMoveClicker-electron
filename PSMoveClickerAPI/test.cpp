#include "PSMC.hpp"
#include <unistd.h>

int main()
{
    PSMC::ControllerManager controllerManager;
    Input::Input input;
    controllerManager.Start();

    for (;;)
    {
        controllerManager.Update();
    }
}