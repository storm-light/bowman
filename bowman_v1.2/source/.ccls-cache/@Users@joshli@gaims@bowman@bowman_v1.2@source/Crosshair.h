#ifndef _CROSSHAIR_H_
#define _CROSSHAIR_H_

#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "HelperFunctions.h"
#include "GlobalVars.h"
#include "Landscape.h"
#include "Bowman.h"

class Crosshair
{

private:

    SDL_Texture * tex;
    SDL_Rect cross;

    int player;

    int x, y;

public:

    Crosshair();
    ~Crosshair();

    void setNum(int playerNum);
    void setPos(int xpos, int ypos);

    void update(float * X, float * Y);
    void render();

};

#endif
