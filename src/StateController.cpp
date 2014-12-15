#include "StateController.h"

StateController::StateController()
{
    //ctor
}

StateController::~StateController()
{
    //dtor
}

void StateController::handleEvent(SDL_Event const& event, StateController::State& state)
{
    switch (event.type)
    {
    case SDL_QUIT:
        state = StateController::EXITING;
        break;

    case SDL_KEYDOWN:

        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            state = StateController::EXITING;
            break;
        default:
            break;
        }

        break;
    }
}
