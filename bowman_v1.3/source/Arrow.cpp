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
#include "Arrow.h"
// fix multiple include header file problem (avoid duplication)

Arrow::Arrow()
{
    x = 0; y = 0;
    x_v = 0;
    y_v = 0;

    // aTex = loadTexture(rend, "arrow.png");

    drawn = 0;
    stuck = 0;

    player = 1;
}

Arrow::Arrow(int angle, int power, int x_p, int y_p, int p)
{
    x_v = power;
    y_v = 0;
    // first assume that angle is always 0
    if (angle == 180)
        x_v = -x_v;
    x = x_p; y = y_p;

    stuck = 1;
    
    player = p;
    
    theta = 0;
}

Arrow::~Arrow()
{
    // SDL_DestroyTexture(aTex);
}

void Arrow::update()
{
    // updates x coordinate
    x += x_v / 60;
    
    if (y < ground && stuck == 0)
        y_v += gravity;

    if (stuck == 0)
        y += y_v / 60;

    // angle of arrow depends on the tangent of the velocities
    if (stuck == 0 || (stuck == 1 && drawn == 1))
        theta = atan ((float) y_v / (float) x_v);
    // printf("%f\n", theta);

    // checks if the tip of the arrow touched anything, if so, arrow stops
    if (player == 1 && (x > winW || y > winH || x < 0 || y < 0))
    {
        x_v = 0;
        y_v = 0;
        stuck = 1;
    }

    if (player == 2 && (x < 0 || y > winH || x > winW || y < 0))
    {
        x_v = 0;
        y_v = 0;
        stuck = 1;
    }

}

void Arrow::render()
{
    // SDL_Rect src = {10, 0, 32, 32};
    // SDL_Rect dest = {x, y, 10, 32};
    // SDL_RendererFlip flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

    if (drawn == 1)
    {
        if (player == 2)
        {
            SDL_RenderDrawPoint(rend, x, y);
            SDL_RenderDrawPoint(rend, x + 32 * cos (theta), y + 32 * sin (theta));
            SDL_RenderDrawLine(rend, x, y, x + 32 * cos (theta), y + 32 * sin (theta));
            // printf("x: %d, y: %d, x+32cos(theta): %f, y+32sin(theta): %f\n", x,y,x+32*cos(theta),y+32*sin(theta));
            // printf("%d, %d\n", x_v, y_v);
        }
        else
        {
            // SDL_RenderCopyEx(rend, aTex, &src, &dest, theta * 180 / PI + 270, NULL, flip);
            SDL_RenderDrawPoint(rend, x, y);
            SDL_RenderDrawPoint(rend, x - 32 * cos (theta), y - 32 * sin (theta));
            SDL_RenderDrawLine(rend, x, y, x - 32 * cos (theta), y - 32 * sin (theta));
        }
    }
    // SDL_RenderCopy(rend, aTex, NULL, &dest);
}

int Arrow::getX()
{
    if (player == 1)
        return (x);
    return x;
}

int Arrow::getY()
{
    if (player == 1)
        return (y);
    return y;
}

void Arrow::unstuck(int angle, int pow, int p)
{
    stuck = 0;

    x_v = pow * cos (PI / 180 * angle);
    y_v = pow * sin (PI / 180 * angle);

}

void Arrow::drawBack(int angle, int power, int x_p, int y_p, int p)
{
    x_v = power * cos (PI / 180 * angle);
    y_v = power * sin (PI / 180 * angle);

    x = x_p; y = y_p;

    stuck = 1;
    drawn = 1;
    
    player = p;

    if (p == 2)
    {
        x_v *= -1;
        y_v *= -1;
    }
}
