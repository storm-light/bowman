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

Bowman::Bowman()
{
    random = 0;
    // variables controlled by input
    up = 0;
    down = 0;
    left = 0;
    right = 0;                  // noooe
    // dir = rightDir + 2;
    angle = 0;      // angle of shot
    power = 0;      // power of shot
    pulling = 0;                // variable for user input - pulling string of bow
    tiltUp = 0;                 // tilts arrow up when shooting
    tiltDown = 0;               // tilts down

    lives = 1;                  // lives for each player; eventually determined by user input
    fuel = 400;
    arrowNum = 0;

    // W/H for rendered Bowman vs. SpriteSheet lengths
    width = 16; height = 16;
    box.w = width; box.h = height;

    x_pos = 0;
    y_pos = 0;
    x_vel = 0;
    y_vel = 0;
    vel = 240;                 // default is 120
    acc = 7;

    lastTime = 0;

    camX = 0; camY = 0;
    cam.w = winW; cam.h = winH;

    arrows = new Arrow[20];
    lastArrow = NULL;

    player = 1;

    tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetRenderTarget(rend, tex);
    SDL_UpdateTexture(tex, NULL, NULL, width * 3);
    SDL_RenderCopy(rend, loadTexture(rend, "white.png"), NULL, NULL);
    // SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    // SDL_RenderFillRect(rend, NULL);
    SDL_SetRenderTarget(rend, NULL);
}

void Bowman::setNum(int playerNum)
{
    player = playerNum;
}

void Bowman::setPos(int x, int y)
{
    x_pos = x;
    y_pos = y;
}

Bowman::~Bowman()
{
    delete[] arrows;
    SDL_DestroyTexture(tex);
}

void Bowman::handleEvents()
{
    if (player == 2)
    {
// KEYDOWN
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                up = 1;
                break;

            case SDLK_DOWN:
                down = 1;
                break;

            case SDLK_LEFT:
                left = 1;
                break;

            case SDLK_RIGHT:
                right = 1;
                break;

            case SDLK_SLASH:
                pulling = 1;
                break;
            }

        }

        //KEYUP
        else if(event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                up = 0;
                break;

            case SDLK_DOWN:
                down = 0;
                break;
            
            case SDLK_LEFT:
                left = 0;
                break;
            
            case SDLK_RIGHT:
                right = 0;
                break;
            
            case SDLK_SLASH:
                pulling = 0;
                break;
            }
        }
    }
    
    if (player == 1)
    {
// KEYDOWN
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_w:
                up = 1;
                break;

            case SDLK_s:
                down = 1;
                break;

            case SDLK_a:
                left = 1;
                break;

            case SDLK_d:
                right = 1;
                break;

            case SDLK_f:
                pulling = 1;
                break;

            case SDLK_g:
                tiltUp = 1;

            case SDLK_h:
                tiltDown = 1;
            }

        }

        //KEYUP
        else if(event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_w:
                up = 0;
                break;

            case SDLK_s:
                down = 0;
                break;
            
            case SDLK_a:
                left = 0;
                break;
            
            case SDLK_d:
                right = 0;
                break;
            
            case SDLK_f:
                pulling = 0;
                break;

            case SDLK_g:
                tiltUp = 0;

            case SDLK_h:
                tiltDown = 0;
            }
        }
    }
}

void Bowman::update(Arrow * opponent)
{
    // movement when bowman is on land
    if (up && !down && fuel > 0)
    {
        y_vel -= gravity + acc;   // upward acc must be > gravity
        if (y_vel < -vel) y_vel = -vel;
        fuel--;
    }
    if (left && !right)
    {
        x_vel -= acc;
        if (x_vel < -vel) x_vel = -vel;
    }
    else if (!left && right)
    {
        x_vel += acc;
        if (x_vel > vel) x_vel = vel;
    }
    else if (y_pos + height >= ground) x_vel *= 0.9; // friction on ground

    // updates x coordinate
    x_pos += x_vel / 60;
    
    // updates y coordinate
    if (y_pos < ground)
        y_vel += gravity;

    y_pos += y_vel / 60;

    // y-axis collision
    if (y_pos + height >= ground)
    {
        y_pos = ground - height;
        y_vel = 0;
        fuel = 400;
    }
    if (y_pos < 0)
    {
        y_pos = 0;
        y_vel = 0;
    }
    
    // collision for x-axis boundary
    if (x_pos < 0) 
    {
        x_pos = 0;
        x_vel = 0;
    }
    if (x_pos + width > winW)
    {
        x_pos = winW - width;
        x_vel = 0;
    }

    if (pulling == 1)
    {
        power += 10;
        if (power > 1000) power = 1000;

        if (up == 1)
            angle += 1;
        if (down == 1)
            angle -= 1;
        if (up == 0 && down == 0)
            angle = 0;

        if (arrowNum < 20)
        {
            if (player == 1)
            {
                angle *= -1;
                arrows[arrowNum].drawBack(angle, 0, x_pos, y_pos + (height / 2), player);
            }
            else
                arrows[arrowNum].drawBack(angle, 0, x_pos + width, y_pos + (height / 2), player);
        }
    }

    if (pulling == 0 && power > 0)
    {
        if (arrowNum < 20)
        {
// the arrow is released with unstuck and thrown with appropriate power (arrowNum is then increased)
            if (player == 1) arrows[arrowNum++].unstuck(angle, power + x_vel, player);  // point of release, arrow is given velocity
            else arrows[arrowNum++].unstuck(angle, -1 * power + x_vel, player); 
        }
        // if (arrowNum >= 20) arrowNum = 20 - 1; // avoids seg fault?
        power = 0;
        angle = 0;
    }

    int i;
    for (i = 0; i < 20; i++)
    {
        arrows[i].update();
    }
    
    for (i = 0; i < 20; i++)
    {
        if (opponent[i].getX() > x_pos && opponent[i].getY() > y_pos && opponent[i].getX() - x_pos < width && opponent[i].getY() - y_pos < height && lastArrow != &opponent[i])
        {
            lives--;
            lastArrow = &opponent[i];
            // attempt to add arrows that hit bowman to its tex
            // SDL_SetRenderTarget(rend, tex);
            // opponent[i].render();
            SDL_Delay(1000);
        }
    }
    
    // printf("Player %d with %d lives\n", player, lives);
}

void Bowman::render()
{
    // rendering Bowman WRT to the cam
    // SDL_Rect renderQuad = {x_pos - camX, y_pos - camY, width, height};
    
    // if (up)
    //     SDL_RenderCopy(rend, SpriteSheet, &clipsUp[currentFrame], &renderQuad);
    // else if (down)
    //     SDL_RenderCopy(rend, SpriteSheet, &clipsDown[currentFrame], &renderQuad);
    // random buffer to stop that annoying spritesheet at the bottom of the screen glitch like wtf m8
    // SDL_Color c = {255,255,255,255};
    // renderText("PLSSS", "Spoopies.ttf", c, 200, 200);
    // lol damn i forgot i misset the renderer target 
    // SDL_RenderCopy(rend, landmap, NULL, NULL);
    // printf("pls\n");
    box.x = x_pos; box.y = y_pos;
    // SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    // SDL_RenderFillRect (rend, &box);

    // SDL_RenderCopy(rend, tex, NULL, &box);
    random++;
    // SDL_RendererFlip flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    SDL_RendererFlip flip = (SDL_RendererFlip) (SDL_FLIP_NONE);
    SDL_RenderCopyEx(rend, tex, NULL, &box, random, NULL, flip);

    int i;
    for (i = 0; i < 20; i++)
    {
        arrows[i].render();
    }
}

Arrow * Bowman::getArrow()
{
    return arrows;
}
