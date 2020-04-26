#ifndef _TITLESCREEN_H_
#define _TITLESCREEN_H_

#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "HelperFunctions.h"
#include "GlobalVars.h"

class Titlescreen : public GameState
{
private:
    // titlescreen background
    // SDL_Texture * bg;

public:
    // initializes the titlescreen's resources
    Titlescreen();
    // cleans up resources
    ~Titlescreen();

    // functions in main loop
    void handleEvents();
    void update();
    void render();
};

#endif
