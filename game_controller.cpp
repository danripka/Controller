//=================================================================================================
// File: game_controller.cpp
// Description: Implements game controller management using SDL2.
// Author: Daniel Ripka
//=================================================================================================

#include "game_controller.h"
#include <chrono>
#include <thread>
#include <vector>

std::vector<GameController::GameController_c *> game_controllers;

void _ClearLastLine(void);

namespace GameController
{
    void Init(void)
    {
        SDL_Init(SDL_INIT_GAMECONTROLLER);

        game_controllers.clear();

        int num_joysticks = SDL_NumJoysticks();

        for (int i = 0; i < num_joysticks; i++)
        {
            if (SDL_IsGameController(i))
            {
                GameController_c *p_game_controller = new GameController_c(i);
                game_controllers.emplace_back(p_game_controller);
            }
        }
    }

    void Quit(void)
    {
        for (GameController_c *p_game_controller : game_controllers)
        {
            delete p_game_controller;
        }

        game_controllers.clear();

        SDL_Quit();
    }

    void Monitor(void)
    {
        SDL_Event event;

        bool running = true;

        SDL_assert(game_controllers.size() > 0);
        GameController_c *p_game_controller = game_controllers[0];

        do
        {
            Axis_struct_t axis = p_game_controller->GetAxis();
            std::cout << "Left Stick (x,y): " << axis.left_x << "," << axis.left_y << std::endl;
            std::cout << "Right Stick (x,y): " << axis.right_x << "," << axis.right_y << std::endl;
            std::cout << "Left Trigger: " << axis.trigger_left << std::endl;
            std::cout << "Right Trigger: " << axis.trigger_right << std::endl;

            _ClearLastLine();

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT ||
                    event.type == SDL_CONTROLLERDEVICEREMOVED)
                {
                    running = false;
                }
            }

        } while (running);
    }

    GameController_c::GameController_c(int id) : _id(id), _handle(nullptr)
    {
        if (SDL_IsGameController(_id))
        {
            _handle = SDL_GameControllerOpen(_id);
        }
    }

    GameController_c::~GameController_c(void)
    {
        if (_handle != nullptr)
        {
            SDL_GameControllerClose(_handle);
        }
    }

    const char *GameController_c::GetPath(void)
    {
        return SDL_GameControllerPath(_handle);
    }

    Axis_struct_t GameController_c::GetAxis(void)
    {
        Axis_struct_t axis{
            .left_x = SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_LEFTX),
            .left_y = SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_LEFTY),
            .right_x = SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_RIGHTX),
            .right_y = SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_RIGHTY),
            .trigger_left = SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_TRIGGERLEFT),
            .trigger_right = SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_TRIGGERRIGHT),
        };
        return axis;
    }

} // namespace GameController

void _ClearLastLine(void)
{
    std::cout << "\033[1A"; // Move cursor up one line
    std::cout << "\033[2K"; // Clear the entire line
    std::cout.flush();
}