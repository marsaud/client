#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <SDL/SDL.h>

#include "Player.h"

class ActionController
{
public:
    ActionController();
    virtual ~ActionController();

    static void handleEvent(SDL_Event const& event, Player::Action& action);
protected:
private:
};

#endif // ACTIONCONTROLLER_H
