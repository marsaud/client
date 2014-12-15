#include "ActionController.h"

ActionController::ActionController()
{
    //ctor
}

ActionController::~ActionController()
{
    //dtor
}

void ActionController::handleEvent(SDL_Event const& event, Player::Action& action)
{
    if (SDL_KEYDOWN == event.type)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_e:
            action = Player::ACTION_ENTER_ZONE;
            break;
        default:
            break;
        }
    }
}
