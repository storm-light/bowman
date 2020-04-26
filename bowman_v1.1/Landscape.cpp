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

Landscape::Landscape()
{
    // fg = loadTexture(rend, "Foreground.png");
    // // change to actual background later
    // bg = loadTexture(rend, "Titlescreen.png");
    
    // landTiles = loadTexture(rend, "Land.png");
    
    space = loadTexture(rend, "Königssee Lake.jpg");
    
    // generateLand();

    // players generated and given numbers
    b1 = new Bowman();
    b2 = new Bowman();
    b2->setNum(2);
    b2->setPos(winW - 32, 0);
}

Landscape::~Landscape()
{
    // SDL_DestroyTexture(fg);
    // SDL_DestroyTexture(bg);
    // SDL_DestroyTexture(landTiles);
    SDL_DestroyTexture(space);
    b1->~Bowman();
    b2->~Bowman();
}

void Landscape::handleEvents()
{
    // while there are any events to process
    while (SDL_PollEvent(&event))
    {
        b1->handleEvents();
        b2->handleEvents();

        // if user wants to quit
        if (event.type == SDL_QUIT)
        {
            //Quit the program
            setNextState(STATE_EXIT);
        }
        // if the user pressed enter
        else if (event.type == SDL_KEYDOWN) 
            switch (event.key.keysym.sym)
            {
            // case SDLK_RIGHT:
            //     // to the lab!
            //     setNextState(STATE_LAB);
            //     break;
            case SDLK_q:
                // to the title!
                setNextState(STATE_EXIT);
                break;
            }
    }
}

void Landscape::update()
{
    b1->update(b2->getArrow());
    b2->update(b1->getArrow());
}

void Landscape::render()
{
    // render background
    // SDL_RenderCopy(rend, bg, NULL, NULL);
    // // render foreground
    // SDL_RenderCopy(rend, fg, NULL, NULL);

    // b1->renderLandCam();
    // SDL_Point * point = NULL; point->x = winW / 2; point->y = winH / 2;
    // SDL_RendererFlip flip = SDL_FLIP_NONE;
    // SDL_RenderCopyEx(rend, space, NULL, NULL, 60, point, flip);
    // SDL_RenderCopy(rend, space, NULL, NULL);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, NULL);
    b1->render();
    b2->render();
    b1->renderCrosshair();
    b2->renderCrosshair();
}

void Landscape::generateLand()
{
    
    int i;
    
    SDL_Texture * Tmap;
    // The creation of all (the map)
    Tmap = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, winW, winH);
    // map set as target so future rendering calls render on the texture map
    SDL_SetRenderTarget(rend, Tmap);

    // creation of thy sky
    SDL_Rect sky; sky.w = winW; // sky.h = baseH + TILE_SIZE;
    sky.h = winH;
    sky.x = 0; sky.y = 0;
    // blue night sky
    // SDL_SetRenderDrawColor(rend, 37, 3, 255, 255);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderFillRect(rend, &sky);
    int luminosity;
    // stars
    for (i = 0; i < 10000; i++)
    {
        luminosity = rand() % 255;
        SDL_SetRenderDrawColor(rend, luminosity, luminosity, 3, 255);
        SDL_RenderDrawPoint(rend, rand() % sky.w, rand() % sky.h);
    }

    SDL_Rect land; land.w = winW; land.h = winH - ground; land.x = 0; land.y = ground;

    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderFillRect(rend, &land);

    landmap = Tmap;
}

// void Landscape::generateLandscape()
// {
//     // time seed
//     srand(time(NULL));

//     // dimensions of landscape using tiles
//     int xTiles = winW / TILE_SIZE; 
//     int yTiles = winH / TILE_SIZE; 
//     // holds data for land and sky tiles
//     int world[xTiles][yTiles];
//     memset(world, 0, sizeof(world[0][0]) * xTiles * yTiles);
//     // number of tiles in the y-axis that marks the line of the ground
//     int baseH = winH * 3 / 4;
//     // baselvl = baseline * TILE_SIZE;

//     int i, j;

//     SDL_Texture * Tmap;
//     // The creation of all (the map)
//     Tmap = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, winW, winH);
//     // map set as target so future rendering calls render on the texture map
//     SDL_SetRenderTarget(rend, Tmap);

//     // creation of thy sky
//     SDL_Rect sky; sky.w = winW; // sky.h = baseH + TILE_SIZE;
//     sky.h = winH;
//     sky.x = 0; sky.y = 0;
//     // blue night sky
//     // SDL_SetRenderDrawColor(rend, 37, 3, 255, 255);
//     SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
//     SDL_RenderFillRect(rend, &sky);
//     int luminosity;
//     // stars
//     for (i = 0; i < 10000; i++)
//     {
//         luminosity = rand() % 255;
//         SDL_SetRenderDrawColor(rend, luminosity, luminosity, 3, 255);
//         SDL_RenderDrawPoint(rend, rand() % sky.w, rand() % sky.h);
//     }
    
//     // creation of land
//     SDL_Rect d; d.w = TILE_SIZE; d.h = TILE_SIZE;
//     SDL_Rect src; src.w = 16; src.h = 16; src.x = 0; 

//     // SDL_RenderClear(rend);
//     // generates terrain!
//     for (i = 0; i < xTiles; i++)
//     {
//         for (j = 0; j < yTiles; j++)
//         {
//             if (j > baseH / TILE_SIZE)
//             {
//                 world[j][i] = 1;
//                 d.x = i * TILE_SIZE; d.y = j * TILE_SIZE;
//                 // and random depth tiles yey
//                 if (j == baseH / TILE_SIZE + 1)
//                 {
//                     src.y = 0;
//                     SDL_RenderCopy(rend, landTiles, &src, &d);
//                 }
//                 // // two 2nd level depth tiles 
//                 else if (j > baseH / TILE_SIZE + 1 && j < baseH / TILE_SIZE + 1 + 3)
//                 {
//                     src.y = 16;
//                     SDL_RenderCopy(rend, landTiles, &src, &d);
//                 }
//                 // // three 3rd level detph tiles
//                 else if (j > baseH / TILE_SIZE + 1 + 2 && j < baseH / TILE_SIZE + 1 + 6)
//                 {
//                     src.y = 32;
//                     SDL_RenderCopy(rend, landTiles, &src, &d);
//                 }
//                 else if (j > baseH / TILE_SIZE + 1 + 5 && j < baseH / TILE_SIZE + 1 + 10)
//                 {
//                     src.y = 48;
//                     SDL_RenderCopy(rend, landTiles, &src, &d);
//                 }
//                 else
//                 {
//                     src.y = 64;
//                     SDL_RenderCopy(rend, landTiles, &src, &d);
//                 }
//             }
//         }
//     }
//     // addss the black void at the bottom of the landscape since the sky was previously visible.
//     sky.y = (baseH / TILE_SIZE + 11) * TILE_SIZE;
//     SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
//     SDL_RenderFillRect(rend, &sky);

//     SDL_Rect lab; lab.x = winW * 2 / 3; lab.y = ground - LAB_H; lab.w = LAB_W; lab.h = LAB_H; 
//     SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
//     SDL_RenderFillRect(rend, &lab);
    
//     // SDL_RenderCopy(rend, bg, NULL, NULL);
//     SDL_SetRenderTarget(rend, NULL);

//     landmap = Tmap;
// }
