#ifndef _BOWMAN_H_
#define _BOWMAN_H_

#include <iostream>
#include <vector>
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
#include "Clone.h"

class Crosshair;
class Clone;

class Bowman
{

private:
    
    int up, down, left, right;
    int angle, aiming, fire;
    int lives;
    std::string livesNum;
    // std::ostringstream convert;
    int infx, infy;             // points at infinity

    int width, height;
    SDL_Rect box, cbox;
    float x_pos, y_pos;
    float x_vel, y_vel;
    float vel;
    float acc;

    std::vector<float> slope, intercept, myX, myY;

    float crossX, crossY;
    Crosshair * crosshair;

    Uint32 lastTime, currentTime;

    int player;

    SDL_Texture * tex;

    std::vector<Clone> clones;
    Clone * ph;
    int clonesNum, deploy, deployed;

    Projectile * m;

public:

    Bowman();
    ~Bowman();

    void setNum(int playerNum);
    void setPos(int x, int y);

    void handleEvents();

    std::vector<int> update(std::vector<float> x, std::vector<float> y);
    void updateLandCam();

    void render(); 
    void renderCrosshair();

    float getSlope();
    float getIntercept();

    std::vector<float> getX();
    std::vector<float> getY();

    void hit(std::vector<int> w);
};

#endif
