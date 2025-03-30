#include "game_controller.h"

int main(int argc, char *argv[])
{
    GameController::Init();

    GameController::Monitor();

    GameController::Quit();

    return 0;
}