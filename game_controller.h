//=================================================================================================
// File: game_controller.h
// Description: Implements game controller management using SDL2.
// Author: Daniel Ripka
//=================================================================================================

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <SDL2/SDL.h>

constexpr uint16_t RumbleIntensity(uint8_t percentage)
{
    return static_cast<uint16_t>((static_cast<uint32_t>(percentage) * 0xFFFF) / 100);
}

namespace GameController
{

    typedef struct
    {
        Sint16 left_x;
        Sint16 left_y;
        Sint16 right_x;
        Sint16 right_y;
        Sint16 trigger_left;
        Sint16 trigger_right;

    } Axis_struct_t;

    typedef struct
    {
        unsigned char red;
        unsigned char green;
        unsigned char blue;

    } RGBColor_struct_t;

    void Init(void);
    void Quit(void);
    void Monitor(void);

    class GameController_c
    {
    private:
        int _id;
        SDL_GameController *_handle;

    public:
        GameController_c(int id);
        ~GameController_c(void);
        const char *GetPath(void);
        Axis_struct_t GetAxis(void);
        // SDL_JoystickGetPlayerIndex
        // SDL_JoystickGetVendor
        // SDL_JoystickGetProduct
        // SDL_JoystickGetProductVersion
        // SDL_JoystickGetFirmwareVersion
        // SDL_JoystickGetSerial
        // SDL_JoystickGetType
        // SDL_JoystickCurrentPowerLevel
        // SDL_JoystickHasRumble
        // SDL_JoystickRumble
        // SDL_JoystickHasRumbleTriggers
        // SDL_JoystickRumbleTriggers
        // SDL_JoystickHasLED
        // SDL_JoystickSetLED
    };
}

#endif