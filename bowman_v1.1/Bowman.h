#ifndef _BOWMAN_H_
#define _BOWMAN_H_

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

class Crosshair;

class Bowman
{

private:
    
    int up, down, left, right;
    int angle, aiming;
    int lives;

    int width, height;
    SDL_Rect box;
    float x_pos, y_pos;
    float x_vel, y_vel;
    float vel;
    float acc;

    float crossX, crossY;
    Crosshair crosshair;

    Uint32 lastTime;

    int player;

    SDL_Texture * tex;

public:

    Bowman();
    ~Bowman();

    void setNum(int playerNum);
    void setPos(int x, int y);

    void handleEvents();

    void update();
    void updateLandCam();

    void render(); 
    void renderCrosshair();

};

#endif
