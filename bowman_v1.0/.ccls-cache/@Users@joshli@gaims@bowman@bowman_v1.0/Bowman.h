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
#include "Arrow.h"


class Bowman
{

private:
    
    int up, down, left, right;
    int angle, power, pulling, tiltUp, tiltDown;
    int used;
    int fuel;
    int arrowNum;               // tells which arrow bowman is on (next being fired)
    // int dir;
    int lives;
    int random;

    int width, height;
    SDL_Rect box;
    float x_pos, y_pos;
    float x_vel, y_vel;
    float vel;
    float acc;

    Uint32 lastTime;

    int camX, camY;
    SDL_Rect cam;

    Arrow * arrows;
    Arrow * lastArrow;

    int player;

    SDL_Texture * tex;

public:

    Bowman();
    ~Bowman();

    void setNum(int playerNum);
    void setPos(int x, int y);

    void handleEvents();

    void update(Arrow * opponent);
    void updateLandCam();

    void render(); // cam will become part of Bowman

    Arrow * getArrow();
};

#endif
