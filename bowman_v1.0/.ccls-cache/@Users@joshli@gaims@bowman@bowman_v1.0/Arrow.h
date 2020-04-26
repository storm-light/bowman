#ifndef _ARROW_H_
#define _ARROW_H_

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

class Bowman;

class Arrow
{

private:

    int x, y;
    // SDL_Point center;
    int x_v, y_v;
    float theta;

    int drawn;                // tells if arrow should be rendered or not
    int stuck;                  // tells if the arrow is stuck in a wall
    // if drawn and stuck it's held by bowman, if drawn but not stuck, then bowman has released it.

    // SDL_Texture * aTex;

    int player;

public:

    Arrow();
    Arrow(int angle, int power, int x_p, int y_p, int p);
    ~Arrow();

    int getX();
    int getY();
    void unstuck(int angle, int pow, int p);
    void drawBack(int angle, int power, int x_p, int y_p, int p);
    
    void update();
    void render();

};

#endif
