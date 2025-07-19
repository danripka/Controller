//=================================================================================================
// File: game_controller.h
// Description: Implements game controller management using SDL2.
// Author: Daniel Ripka
//=================================================================================================

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>

constexpr uint32_t ScalePercentageToValue(uint8_t percentage)
{
    if (percentage > 100)
    {
        percentage = 100;
    }
    return static_cast<uint32_t>((static_cast<uint64_t>(percentage) * 0xFFFFFFFF) / 100);
}

namespace GameController
{
    typedef SDL_GameControllerType Type_enum_t;

    typedef SDL_GameControllerButton Button_enum_t;

    typedef struct
    {
        int16_t left_x;
        int16_t left_y;
        int16_t right_x;
        int16_t right_y;
        int16_t trigger_left;
        int16_t trigger_right;

    } Axis_struct_t;

    typedef struct
    {
        unsigned char red;
        unsigned char green;
        unsigned char blue;

    } RGBColor_struct_t;

    void Init(void);
    void Quit(void);
    void PollEvents(void);

    class GameController_c
    {
    private:
        SDL_GameController *_handle;

    public:
        GameController_c(int id);
        ~GameController_c(void);
        // TODO: Mappings
        const char *GetName(void);
        const char *GetPath(void);
        Type_enum_t GetType(void);
        int GetIndex(void);
        uint16_t GetVendor(void);
        uint16_t GetProductId(void);
        uint16_t GetProductVersion(void);
        uint16_t GetFirmwareVersion(void);
        const char *GetSerialNumber(void);
        bool IsConnected(void);
        Axis_struct_t GetAxis(void);
        uint8_t GetButton(Button_enum_t button);
        // TODO: Touchpad
        // TODO: Sensor
        int Rumble(uint8_t low_freq, uint8_t high_freq, uint32_t duration_ms);
        int RumbleTriggers(uint8_t left_intensity_percentage, uint8_t right_intensity_percentage, uint32_t duration_ms);
        int SetLED(RGBColor_struct_t rgb);
    };
}

#endif