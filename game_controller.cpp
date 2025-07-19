//=================================================================================================
// File: game_controller.cpp
// Description: Implements game controller management using SDL2.
// Author: Daniel Ripka
//=================================================================================================

#include "game_controller.h"

namespace GameController
{

    void Init(void)
    {
        // Initialize the controller and joystick subsystems.
        SDL_Init(SDL_INIT_GAMECONTROLLER);
    }

    void Quit(void)
    {
        SDL_Quit();
    }

    void PollEvents(void)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_CONTROLLERAXISMOTION: // Game controller axis motion
                break;
            case SDL_CONTROLLERBUTTONDOWN: // Game controller button pressed
                break;
            case SDL_CONTROLLERBUTTONUP: // Game controller button released
                break;
            case SDL_CONTROLLERDEVICEADDED: // A new Game controller has been inserted into the system
                break;
            case SDL_CONTROLLERDEVICEREMOVED: // An opened Game controller has been removed
                break;
            case SDL_CONTROLLERDEVICEREMAPPED: // The controller mapping was updated
                break;
            case SDL_CONTROLLERTOUCHPADDOWN: // Game controller touchpad was touched
                break;
            case SDL_CONTROLLERTOUCHPADMOTION: // Game controller touchpad finger was moved
                break;
            case SDL_CONTROLLERTOUCHPADUP: // Game controller touchpad finger was lifted
                break;
            case SDL_CONTROLLERSENSORUPDATE: // Game controller sensor was updated
                break;
            default:
                break;
            }
        }
    }

    GameController_c::GameController_c(int id) : _handle(nullptr)
    {
        if (SDL_IsGameController(id))
        {
            _handle = SDL_GameControllerOpen(id);
        }
    }

    GameController_c::~GameController_c(void)
    {
        SDL_GameControllerClose(_handle);
    }

    const char *GameController_c::GetName(void)
    {
        return SDL_GameControllerName(_handle);
    }

    const char *GameController_c::GetPath(void)
    {
        return SDL_GameControllerPath(_handle);
    }

    Type_enum_t GameController_c::GetType(void)
    {
        return static_cast<Type_enum_t>(SDL_GameControllerGetType(_handle));
    }

    int GameController_c::GetIndex(void)
    {
        return SDL_GameControllerGetPlayerIndex(_handle);
    }

    uint16_t GameController_c::GetVendor(void)
    {
        return SDL_GameControllerGetVendor(_handle);
    }

    uint16_t GameController_c::GetProductId(void)
    {
        return SDL_GameControllerGetProduct(_handle);
    }

    uint16_t GameController_c::GetProductVersion(void)
    {
        return SDL_GameControllerGetProductVersion(_handle);
    }

    uint16_t GameController_c::GetFirmwareVersion(void)
    {
        return SDL_GameControllerGetFirmwareVersion(_handle);
    }

    const char *GameController_c::GetSerialNumber(void)
    {
        return SDL_GameControllerGetSerial(_handle);
    }

    bool GameController_c::IsConnected(void)
    {
        return SDL_GameControllerGetAttached(_handle);
    }

    Axis_struct_t GameController_c::GetAxis(void)
    {
        Axis_struct_t axis = {
            .left_x = static_cast<int16_t>(SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_LEFTX)),
            .left_y = static_cast<int16_t>(SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_LEFTY)),
            .right_x = static_cast<int16_t>(SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_RIGHTX)),
            .right_y = static_cast<int16_t>(SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_RIGHTY)),
            .trigger_left = static_cast<int16_t>(SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_TRIGGERLEFT)),
            .trigger_right = static_cast<int16_t>(SDL_GameControllerGetAxis(_handle, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)),
        };
        return axis;
    }

    uint8_t GameController_c::GetButton(Button_enum_t button)
    {
        return SDL_GameControllerGetButton(_handle, button);
    }

    int GameController_c::Rumble(uint8_t low_freq_percentage, uint8_t high_freq_percentage, uint32_t duration_ms)
    {
        const uint16_t low_freq_intensity = ScalePercentageToValue(low_freq_percentage);
        const uint16_t high_freq_intensity = ScalePercentageToValue(high_freq_percentage);
        return SDL_GameControllerRumble(_handle, low_freq_intensity, high_freq_intensity, duration_ms);
    }

    int GameController_c::RumbleTriggers(uint8_t left_intensity_percentage, uint8_t right_intensity_percentage, uint32_t duration_ms)
    {
        const uint16_t left_intensity = ScalePercentageToValue(left_intensity_percentage);
        const uint16_t right_intensity = ScalePercentageToValue(right_intensity_percentage);
        return SDL_GameControllerRumbleTriggers(_handle, left_intensity, right_intensity, duration_ms);
    }

    int GameController_c::SetLED(RGBColor_struct_t rgb)
    {
        return SDL_GameControllerSetLED(_handle, rgb.red, rgb.green, rgb.blue);
    }

} // namespace GameController