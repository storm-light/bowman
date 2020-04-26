#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "HelperFunctions.h"
#include "GlobalVars.h"
#include "Titlescreen.h"
#include "Landscape.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_Window * win = NULL;
SDL_Renderer * rend = NULL;

void setNextState(int state)
{
    if (nextState != STATE_EXIT)
        nextState = state;
}

void changeState()
{
    //If the state needs to be changed
    if (nextState != STATE_NULL)
    {
        //Delete the current state
        if (nextState != STATE_EXIT)
        {
            delete currentState;
        }

        //Change the state
        switch (nextState)
        {
            case STATE_TITLE:
                currentState = new Titlescreen();
                break;

            case STATE_LANDSCAPE:
                currentState = new Landscape();
                break;

        }

        //Change the current state ID
        stateID = nextState;

        //NULL the next state ID
        nextState = STATE_NULL;
    }
}

void cleanUp()
{
    // deletes the game state and frees its resources
    delete currentState;

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    
    TTF_Quit();
    SDL_Quit();
}

bool init()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return false;
    } 
    
    if (TTF_Init() != 0)
    {
        std::cout << "TTF Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // window with defined dimensions and in center of screen
    win = SDL_CreateWindow("Bowman",
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    // fullscreen!
    // SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!win)
    {
        std::cout << "Window Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // renderer sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(win, -1, render_flags);
   
    if (!rend)
    {
        std::cout << "Renderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return false;
    }
   
    // gets the fullscreen window dimensions
    SDL_GL_GetDrawableSize(win, &winW, &winH); 
    // ground = 6 * winH / 7;
    // winW = 1900; winH = 1200;
    ground = winH;
    // SDL_GetWindowSize(win, &winW, &winH);
    printf("%d, %d\n", winW, winH);
    // SDL_RenderSetLogicalSize(rend, 1920, 1200);

    return true;
}

SDL_Texture * loadTexture(SDL_Renderer * rend, std::string file)
{
    SDL_Texture * t = NULL;

    SDL_Surface * image = IMG_Load(file.c_str());

    if (image != NULL)
    {
        t = SDL_CreateTextureFromSurface(rend, image);

        SDL_FreeSurface(image);

        if (t == NULL)
        {
            std::cout << "jkTexture error: " << SDL_GetError() << std::endl;
        }
    }

    else
    {
        std::cout << "Surface Init error: " << SDL_GetError() << std::endl;
    }

    return t;
}

void renderText(std::string message, std::string fontFile, SDL_Color color, int fontSize, int y)
{
    /* opens font */
    TTF_Font * font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == 0)
    {
        std::cout << "TTF OPENfont: " << SDL_GetError() << std::endl;
    }

    /* render surface first with TTF_RenderText then create a texture for the surface */
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    if (surf == 0)
    {
        TTF_CloseFont(font);
        std::cout << "TTF RenderText: " << SDL_GetError() << std::endl;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surf);
	if (texture == NULL){
        std::cout << "Create Texture : " << SDL_GetError() << std::endl;
	}

    SDL_Rect d;
    SDL_QueryTexture(texture, NULL, NULL, &d.w, &d.h);
    d.x = (winW - d.w) / 2; d.y = y;
    SDL_RenderCopy(rend, texture, NULL, &d);

    /* frees stuff up */
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture); // fucking TwinkleBear Dev FUCK HIM
	TTF_CloseFont(font);
}
