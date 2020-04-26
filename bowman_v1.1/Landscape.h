#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "HelperFunctions.h"
#include "GameState.h"
#include "GlobalVars.h"

class Bowman;

class Landscape : public GameState
{
private:
    // foreground where Yahdu walks
    // SDL_Texture * fg;
    // // far away background
    // SDL_Texture * bg;
    // // different depth land tiles
    // SDL_Texture * landTiles;
    SDL_Texture * space;
    // // map texture which all tiles are blitted onto
    // SDL_Texture * landmap;

    Bowman * b1;
    Bowman * b2;
    
public:

    Landscape();
    ~Landscape();
    
    void handleEvents();
    void update();
    void render();

    void generateLand();
    void generateLandscape();
};

#endif
