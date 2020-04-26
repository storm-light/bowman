#ifndef _HELPERFUNCTIONS_H_
#define _HELPERFUNCTIONS_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

SDL_Texture * loadTexture(SDL_Renderer * rend, std::string file);

bool init();

void renderText(std::string message, std::string fontFile, SDL_Color color, int fontSize, int y);

void setNextState(int state);
void changeState(); 
void cleanUp();

#endif
