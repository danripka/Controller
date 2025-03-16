#include "controller.h"
#include <chrono>
#include <thread>

static int num_game_controllers = 0;

void ClearLastLine(void)
{
    std::cout << "\033[1A"; // Move cursor up one line
    std::cout << "\033[2K"; // Clear the entire line
    std::cout.flush();
}

int MonitorGameController(int i)
{
    SDL_GameController *controller = SDL_GameControllerOpen(i);

    if (controller != nullptr)
    {
        num_game_controllers++;

        std::cout << "Name: " << SDL_GameControllerName(controller) << "\n";
        std::cout << "Path: " << SDL_GameControllerPath(controller) << "\n";

        printf("\n");

        // Print any missing buttons
        for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
        {
            if (!SDL_GameControllerHasButton(controller, (SDL_GameControllerButton)i))
            {
                std::cout << "Missing button " << SDL_GameControllerGetStringForButton((SDL_GameControllerButton)i) << "\n";
            }
        }

        if (SDL_GameControllerHasRumble(controller))
        {
            SDL_GameControllerRumble(controller, rumble_intensity_medium, rumble_intensity_medium, 1000);
        }

        if (SDL_GameControllerHasRumbleTriggers(controller))
        {
            SDL_GameControllerRumbleTriggers(controller, rumble_intensity_medium, rumble_intensity_medium, 1000);
        }

        if (SDL_GameControllerHasLED(controller))
        {
            RGBColor Teal = {0, 128, 128};
            SDL_GameControllerSetLED(controller, Teal.red, Teal.green, Teal.blue);
        }

        printf("\n");

        bool running = true;
        SDL_Event event;

        while (running)
        {
            Sint16 left_x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
            Sint16 left_y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
            std::cout << "Left Stick (x,y): " << left_x << "," << left_y << "\n";

            Sint16 right_x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
            Sint16 right_y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
            std::cout << "Right Stick (x,y): " << right_x << "," << right_y << "\n";

            Sint16 l_trigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
            std::cout << "Left Trigger: " << l_trigger << "\n";

            Sint16 r_trigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
            std::cout << "Right Trigger: " << r_trigger << "\n";

            // Block for 10 milliseconds
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            // Clear the last four lines
            ClearLastLine();
            ClearLastLine();
            ClearLastLine();
            ClearLastLine();

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT ||
                    event.type == SDL_CONTROLLERDEVICEREMOVED)
                {
                    running = false;
                }
            }

        } // End of 'while' loop
    }
    else
    {
        std::cout << "Failed to open game controller " << i << ": " << SDL_GetError() << "\n";
    }

    SDL_GameControllerClose(controller);

    return 0;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_GAMECONTROLLER);

    int num_joysticks = SDL_NumJoysticks();
    std::cout << "Number of joysticks detected: " << num_joysticks << "\n\n";

    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            MonitorGameController(i);
        }
    }

    SDL_Quit();

    return 0;
}