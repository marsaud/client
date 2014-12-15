#include "MovementController.h"

MovementController::MovementController()
{
    //ctor
}

MovementController::~MovementController()
{
    //dtor
}

void MovementController::handleEvent(SDL_Event const& event, Player::Move& move)
{
    if (SDL_KEYDOWN == event.type)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP :
            move = Player::MOVE_UP;
            break;
        case SDLK_DOWN :
            move = Player::MOVE_DOWN;
            break;
        case SDLK_LEFT :
            move = Player::MOVE_LEFT;
            break;
        case SDLK_RIGHT :
            move = Player::MOVE_RIGHT;
            break;
        default :
            break;
        }
    }
}
