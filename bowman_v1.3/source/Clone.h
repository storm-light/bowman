#ifndef _CLONE_H_
#define _CLONE_H_

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
#include "Crosshair.h"

class Clone
{

private:

    float x, y;
    int lives;

public:

    Clone(float xx, float yy);
    
    int placed();
    int getLives();
    
    float getX();
    float getY();

};

#endif
