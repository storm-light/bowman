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
#include "Titlescreen.h"

Titlescreen::Titlescreen()
{
    // bg = loadTexture(rend, "Welsome.png");
}

Titlescreen::~Titlescreen()
{
    // SDL_DestroyTexture(bg);
}

void Titlescreen::handleEvents()
{
    // while there are any events to process
    while (SDL_PollEvent(&event))
    {
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
            case SDLK_q:
                //Quit the program
                setNextState(STATE_EXIT);
                break;
            case SDLK_RETURN:
                // to the lands!
                setNextState(STATE_LANDSCAPE);
                printf("Returned!\n");
                break;
            }
    }
}

void Titlescreen::update()
{
    
}

void Titlescreen::render()
{
    // render background
    // SDL_RenderCopy(rend, bg, NULL, NULL);
    // render title
    SDL_Color c = {149, 179, 199, 255};
    renderText("BOWMAN", "Spoopies.ttf", c, 150, -1, 100); 

    // render "Press Enter" message
    SDL_Color ca = {255, 255, 255, 255};
    renderText("PRESS ENTER", "Spoopies.ttf", ca, 50, -1, 700);
}

