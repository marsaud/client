#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H

#include <SDL/SDL.h>


class StateController
{
public:
    StateController();
    virtual ~StateController();

    enum State
    {
        IDLE, CONNECTING, INITIALIZING, PLAYING, EXITING
    };

    static void handleEvent(SDL_Event const& event, StateController::State& state);
protected:
private:
};

#endif // STATECONTROLLER_H
