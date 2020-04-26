#include "Crosshair.h"

Crosshair::Crosshair()
{
    cross.w = 16; cross.h = 16;
    x = 0; y = 0;
    tex = loadTexture(rend, "cross2.png");
}

Crosshair::~Crosshair()
{
    SDL_DestroyTexture(tex);
}

void Crosshair::setNum(int playerNum)
{
    player = playerNum;
}

void Crosshair::setPos(int xpos, int ypos)
{
    x = xpos;
    y = ypos;
}

void Crosshair::update(float * X, float * Y)
{
    if (y + cross.h >= ground)
    {
        y = ground - cross.h;
    }
    if (y < 0)
    {
        y = 0;
    }
        
    // collision for x-axis boundary
    if (x < 0) 
    {
        x = 0;
    }
    if (x + cross.w > winW)
    {
        x = winW - cross.w;
    }
    *X = x;
    *Y = y;
}

void Crosshair::render()
{
    cross.x = x; cross.y = y;
    SDL_RenderCopy(rend, tex, NULL, &cross);
}
