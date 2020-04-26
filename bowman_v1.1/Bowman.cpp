#include "Bowman.h"
// fix multiple include header file problem (avoid duplication)

Bowman::Bowman()
{
    // variables controlled by input
    up = 0;
    down = 0;
    left = 0;
    right = 0;                  // noooe

    angle = 0;      // angle of shot
    aiming = 0;

    lives = 3;                  // lives for each player; eventually determined by user input

    // W/H for rendered Bowman vs. SpriteSheet lengths
    width = 16; height = 16;
    box.w = width; box.h = height;

    // crosshair
    crosshair = new Crosshair();
    crossX = 0; crossY = 0;

    x_pos = 0;
    y_pos = 0;
    x_vel = 0;
    y_vel = 0;
    vel = 240;                 // default is 120
    acc = 7;

    lastTime = 0;

    player = 1;

    tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetRenderTarget(rend, tex);
    SDL_UpdateTexture(tex, NULL, NULL, width * 3);
    SDL_RenderCopy(rend, loadTexture(rend, "white.png"), NULL, NULL);
    // SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    // SDL_RenderFillRect(rend, NULL);
    SDL_SetRenderTarget(rend, NULL);
}

Bowman::~Bowman()
{
    SDL_DestroyTexture(tex);
    crosshair.~Crosshair();
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
                aiming = 1;
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
                aiming = 2;
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
                aiming = 1;
                break;

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
                aiming = 2;
                break;

            }
        }
    }
}

void Bowman::update()
{
    // movement when bowman is on land
    if (up && !down)
    {
        y_vel -=  acc;   
        if (y_vel < -vel) y_vel = -vel;
    }
    if (!up && down)
    {
        y_vel +=  acc;   
        if (y_vel > vel) y_vel = vel;
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
    if (!left && !right) x_vel *= 0.9; // friction on ground
    if (!up && !down) y_vel *= 0.9; // friction on ground

    // updates x coordinate
    x_pos += x_vel / 60;
    
    // updates y coordinate
    y_pos += y_vel / 60;

    // y-axis collision
    if (y_pos + height >= ground)
    {
        y_pos = ground - height;
        y_vel = 0;
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

    if (aiming == 1)
    {
        // add updates for moving crosshair
        if (up && !down)
        {
            crossY -= vel;
        }
        if (!up && down)
        {
            crossY += vel;
        }
        if (left && !right)
        {
            crossX -= vel;
        }
        else if (!left && right)
        {
            crossX += vel;
        }
    }

    if (aiming == 2)
    {
        // 2 when user presses "fire" for second time (shooting all clones at crosshair)
        aiming = 0;
    }

    crosshair.setPos(crossX, crossY);

}

void Bowman::render()
{
    box.x = x_pos; box.y = y_pos;

    // SDL_RendererFlip flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    if (lives > 0)
        SDL_RenderCopy(rend, tex, NULL, &box);

}

void Bowman::renderCrosshair()
{
    crosshair->render();
}
