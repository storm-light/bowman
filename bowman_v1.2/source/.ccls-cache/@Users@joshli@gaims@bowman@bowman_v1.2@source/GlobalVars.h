#ifndef _GLOBALVARS_H_
#define _GLOBALVARS_H_

#include "GameState.h"
#include "Bowman.h"

#define LAND_W (1280)
#define PI 3.14159265

extern int ground;

extern int stateID;

extern int nextState;

extern GameState * currentState;

extern SDL_Texture * landmap;

extern SDL_Renderer * rend;
extern SDL_Window * win;

extern SDL_Event event;

extern int winW;
extern int winH;

extern SDL_Color white;

extern int gravity;

//Game states
enum GameStates
{
    STATE_NULL,
    STATE_TITLE,
    STATE_LANDSCAPE,
    STATE_EXIT,
};

#endif
