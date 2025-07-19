#include "game_controller.h"
#include <iostream>

int main(int argc, char *argv[])
{
    GameController::Init();

    GameController::GameController_c Controller(0);
    if (Controller.IsConnected())
    {
        std::cout << Controller.GetName() << std::endl;
        std::cout << Controller.GetPath() << std::endl;
        std::cout << Controller.GetType() << std::endl;
        std::cout << Controller.GetIndex() << std::endl;
        std::cout << Controller.GetVendor() << std::endl;
        std::cout << Controller.GetProductId() << std::endl;
        std::cout << Controller.GetProductVersion() << std::endl;
        std::cout << Controller.GetFirmwareVersion() << std::endl;
        std::cout << Controller.GetSerialNumber() << std::endl;
        std::cout << Controller.Rumble(20, 80, 1000) << std::endl;
        std::cout << Controller.RumbleTriggers(20, 80, 1000) << std::endl;
        std::cout << Controller.SetLED({.red = 0, .green = 128, .blue = 128}) << std::endl;

        GameController::PollEvents();
    }

    GameController::Quit();

    return 0;
}