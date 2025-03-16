#include <iostream>
#include <SDL2/SDL.h>

constexpr Uint16 rumble_intensity_medium = 0xFFFF / 2;

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

} RGBColor;

class Controller
{
private:
    int _device_index;

public:
    Controller(int device_index);
    //  : _device_index(device_index) {}

    const char *GetPath(); // SDL_JoystickPath
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

// bool Init() { return (SDL_Init(SDL_INIT_JOYSTICK) != 0); }

// const char *GetError() { return SDL_GetError(); }

// int GetNumberOfJoysticks() {}
