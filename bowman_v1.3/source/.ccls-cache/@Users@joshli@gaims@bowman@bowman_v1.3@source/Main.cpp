#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "HelperFunctions.h"
#include "GlobalVars.h"
#include "Titlescreen.h"
#include "Landscape.h"
#include "Bowman.h"

// current state ID
int stateID = STATE_NULL;
// direction of entrance/exit when switching states
int rightDir = 0;
// next state's ID
int nextState = STATE_NULL;

GameState * currentState = NULL;

SDL_Texture * landmap = NULL;

SDL_Event event;

int winW, winH;

int ground = 1000;
int gravity = 5;

SDL_Color white = {255, 255, 255, 255};

int pNum = 0;

int main()
{
    if (!init())
    {
        return 1;
    }

    // current state ID
    stateID = STATE_TITLE;

    // starts off with title game state
    currentState = new Titlescreen();
    
    while (stateID != STATE_EXIT)
    {
        // handles events for current state
        currentState->handleEvents();
        // updates anything, finish computations
        currentState->update();
        // if need be, change the state
        changeState();
        // renderrrp
        SDL_RenderClear(rend);
        currentState->render();
        SDL_RenderPresent(rend);

        // printf("stateID: %d\n", stateID);

        // 60 fps
        SDL_Delay(1000 / 60);
    }
    
    // Landscape * yee = new Landscape();
    // yee->generateLand();
    // delete yee;
    cleanUp();

    return 0;
        
}
