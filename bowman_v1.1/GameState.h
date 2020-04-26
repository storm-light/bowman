#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "HelperFunctions.h"

class GameState
{
public:
    // main functions in game loop for all states
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    // deconstructor for specific cleanup?
    virtual ~GameState(){};
};

#endif
