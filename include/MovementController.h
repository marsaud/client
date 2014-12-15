#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H

#include <SDL/SDL.h>

#include "Player.h"

class MovementController
{
public:
    MovementController();
    virtual ~MovementController();

    static void handleEvent(SDL_Event const& event, Player::Move& move);
protected:
private:
};

#endif // MOVEMENTCONTROLLER_H
