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

void Crosshair::update()
{

}

void Crosshair::render()
{
    cross.x = x; cross.y = x;
    SDL_RenderCopy(rend, tex, NULL, &cross);
}
