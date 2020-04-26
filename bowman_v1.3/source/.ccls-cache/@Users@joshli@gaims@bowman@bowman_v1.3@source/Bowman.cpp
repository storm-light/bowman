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

    lives = 5;                  // lives for each player; eventually determined by user input
    clonesNum = 0;
    deploy = 0; deployed = 0;

    // W/H for rendered Bowman vs. SpriteSheet lengths
    width = 16; height = 16;
    box.w = width; box.h = height;
    cbox.w = width; cbox.h = height;

    // crosshair
    crosshair = new Crosshair();
    crossX = 0; crossY = 0;

    // clones

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
    crosshair->~Crosshair();
}

void Bowman::setNum(int playerNum)
{
    player = playerNum;
    if (player == 2)
    {
        x_pos = winW-width;
        crossX = winW-width; 
    }
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
                aiming++;
                break;

            case SDLK_PERIOD:
                deploy = 1;
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
                // aiming = 2;
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
                aiming++;
                break;

            case SDLK_g:
                deploy = 1;
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
                // aiming = 2;
                break;

            }
        }
    }
}

std::vector<int> Bowman::update(std::vector<float> x, std::vector<float> y)
{
    std::vector<int> returnV;

    if (aiming == 0)
    {
// movement when bowman is on land
        if (up && !down)
        {
            y_vel =  -vel;   
            if (y_vel < -vel) y_vel = -vel;
        }
        if (!up && down)
        {
            y_vel =  vel;   
            if (y_vel > vel) y_vel = vel;
        }
        if (left && !right)
        {
            x_vel = -vel;
            if (x_vel < -vel) x_vel = -vel;
        }
        if (!left && right)
        {
            x_vel = vel;
            if (x_vel > vel) x_vel = vel;
        }
        if ((!left && !right) || (left && right)) x_vel = 0; 
        if ((!up && !down) || (up && down)) y_vel = 0; 
        // if ((!left && !right) || (left && right)) x_vel *= 0.9; // friction on ground
        // if ((!up && !down) || (up && down)) y_vel *= 0.9; // friction on ground

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
    }
    
    else if (aiming == 1)
    {
        // add updates for moving crosshair
        if (up && !down)
        {
            crossY -= vel / 60;
        }
        if (!up && down)
        {
            crossY += vel / 60;
        }
        if (left && !right)
        {
            crossX -= vel / 60;
        }
        if (!left && right)
        {
            crossX += vel / 60;
        }
    }


    else                        // when aiming == 2
    {
        // 2 when user presses "fire" for second time (shooting all clones at crosshair)
        fire = 1;

        aiming = 0;

        // generates vector of slopes/intercepts

        // slope = (y_pos - (crossY)) / (x_pos - (crossX));
        // intercept = (y_pos + height / 2 - slope * (x_pos + width / 2));

        slope.push_back((y_pos - (crossY)) / (x_pos - (crossX)));
        intercept.push_back(y_pos + height / 2 - slope.back() * (x_pos + width / 2));
        myX.push_back(x_pos);
        myY.push_back(y_pos);

        for (std::vector<Clone>::iterator it = clones.begin(); it != clones.end(); ++it)
        {
            slope.push_back((it->getX() - crossY) / (it->getY() - crossX));
            intercept.push_back(it->getY() + height / 2 - slope.back() * (it->getX() + width / 2));
            myX.push_back(it->getX());
            myY.push_back(it->getY());
        }

        // projectiles created and launched
        m = new Projectile();
        m->x = x_pos;
        m->y = y_pos;
        m->xV = vel / (pow((y_pos - (crossY)) / (x_pos - (crossX)), 2) + 1);
        m->yV = m->xV * (y_pos - (crossY)) / (x_pos - (crossX));
        projectiles.push_back(*m);

        for (i = 0; i < slope.size(); i++)
        {
            m = new Projectile(); // projectile needs to be vector since a clone can have multiple projectiles at once. 
            m->x = myX.at(i);
            m->y = myY.at(i);
            m->xV = vel / (pow(slope.at(i), 2) + 1);
            m->yV = m->xV * slope.at(i);
            projectiles.push_back(*m);
        }

        for (i = 0; i < pNum; i++)
        {
            if (projectiles.at(i)->player != player)
                continue;
            for (j = 0; j < x.size(); j++)
            {
                if ((projectiles.at(i)->x - x.at(j) < width) && (projectiles.at(i)->x - x.at(j) > 0) && (projectiles.at(i)->y - y.at(j) < height) && (projectiles.at(i)->y - y.at(j) > 0))
                {
                    returnV.push_back(j);
                    projectiles.erase(i);
                    pNum--;
                }
            }
        }

        // slopes collision detection:
        // checks to see if the line hits the left or right side of box, or if it goes through top and bottom (in which case the left and right sides aren't touched)
        // int i,j;
        // for (i = 0; i < x.size(); i++)
        // {
        //     for (j = 0; j < slope.size(); j++)
        //     {
        //         if ((((slope.at(j) * x.at(i) + intercept.at(j)) > y.at(i)) && ((slope.at(j) * x.at(i) + intercept.at(j)) < y.at(i) + height)) ||
        //             (((slope.at(j) * (x.at(i) + width) + intercept.at(j)) > y.at(i)) && ((slope.at(j) * (x.at(i) + width) + intercept.at(j)) < y.at(i) + height)) ||
        //             (((slope.at(j) * x.at(i) + intercept.at(j)) < y.at(i)) && ((slope.at(j) * (x.at(i) + width) + intercept.at(j)) > y.at(i) + height)) ||
        //             (((slope.at(j) * (x.at(i) + width) + intercept.at(j)) < y.at(i)) && ((slope.at(j) * x.at(i) + intercept.at(j)) > y.at(i) + height)))
        //         {
        //             printf("on the line\n");
        //             // checks if crosshair and enemy are on the same side
        //             if ((crossX <= myX.at(j) && myX.at(j) >= x.at(i)) ||
        //                 (crossX >= myX.at(j) && myX.at(j) <= x.at(i)) 
        //                 )
        //             {
        //                 printf("hit\n");
        //                 // SDL_Delay(1000);
        //                 if (i == 0)
        //                 {
        //                     returnV.push_back(0);
        //                 }
        //                 else
        //                 {
        //                     returnV.push_back(i);
        //                     break;
        //                 }
        //             }
        //         }
        //         // case where the slope is inf
        //         else if (myX.at(j) == crossX)
        //             // if the line of fire hits
        //             if (myX.at(j) + width / 2 >= x.at(i) && myX.at(j) + width / 2 <= x.at(i) + width)
        //                 // checks if crosshair and enemy are on the same side
        //                 if ((crossY <= myY.at(j) && myY.at(j) >= y.at(i)) ||
        //                     (crossY >= myY.at(j) && myY.at(j) <= y.at(i)))
        //                 {
        //                     printf("hit\n");
        //                     // SDL_Delay(1000);
        //                     if (i == 0)
        //                     {
        //                         returnV.push_back(0);
        //                     }
        //                     else
        //                     {
        //                         returnV.push_back(i);
        //                         break;
        //                     }
        //                 }
        //     }
        // }
        // should be matching this bowman's line to the other bowman's hitbox (not the other way around)
        // ! if same clone is hit multiple times, it could cause the segmentation fault
    }

    crosshair->setPos(crossX, crossY);
    crosshair->update(&crossX, &crossY);

    // updates amount of clones based on time of life
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 0.5 * 1000 && lives > 0)
    {
        clonesNum++;
        lastTime = currentTime;
    }

    if (deploy == 1 && clonesNum - deployed > 0)
    {
        ph = new Clone(x_pos, y_pos);
        clones.push_back(*ph);
        deploy = 0;
        deployed++;
    }
    // int i;
    // for (i = 0 ; i < x.size(); i++)
    // {
    //     printf ("(%f, %f) ", x.at(i), y.at(i));
    // }

    return returnV;
}

void Bowman::render()
{
    box.x = x_pos; box.y = y_pos;

    // fix dpi
    // SDL_RendererFlip flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    // SDL_RenderCopyEx(rend, tex, NULL, &box, angle++, NULL, flip);
    if (lives > 0)
    {
        for (std::vector<Clone>::iterator it = clones.begin(); it != clones.end(); ++it)
        {
            cbox.x = it->getX(); cbox.y = it->getY();
            SDL_RenderCopy(rend, tex, NULL, &cbox);
        }

        SDL_RenderCopy(rend, tex, NULL, &box);
        // sprintf(livesNum, "%d", lives);
        // convert << lives;
        livesNum = std::to_string(lives);
        // livesNum = convert.str();
        SDL_Color c = {120,138,132,255};
        renderText(livesNum, "Spoopies.ttf", c, 16, x_pos + width / 2, y_pos + height / 2);
        livesNum = std::to_string(clonesNum - deployed);
        SDL_Color co = {255,177,10,255};
        renderText(livesNum, "Spoopies.ttf", co, 16, x_pos + width / 2, y_pos - height / 2);
    }
    // use GRID to make particle trail gradient
    // if (fire == 1)
    // {
    //     SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        
    //     infx = 80000 * (x_pos - (crossX)); 
    //     infy = 80000 * (y_pos - (crossY)); 
    //     SDL_RenderDrawLine(rend, x_pos + width / 2, y_pos + height / 2, x_pos + width / 2 - infx, y_pos + height / 2 - infy);
    //     for (std::vector<Clone>::iterator it = clones.begin(); it != clones.end(); ++it)
    //     {
    //         infx = 80000 * (it->getX() - (crossX)); // large multiplier to make sure inf point is offscreen
    //         infy = 80000 * (it->getY() - (crossY)); // large multiplier to make sure inf point is offscreen
    //         SDL_RenderDrawLine(rend, it->getX() + width / 2, it->getY() + height / 2, it->getX() + width / 2 - infx, it->getY() + height / 2 - infy);
    //     }
    //     fire = 0;
    // }

    if (fire == 1)
    {
        int i;

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

        // do projectile rendering in landscape
        for (i = 0; i < pNum; i++)
        {
            
        }

        fire = 0;
    }
}

void Bowman::renderCrosshair()
{
    crosshair->render();
}

float Bowman::getSlope()
{
    if (player == 1)
        printf("slope is %f\n", - (box.y - (crossY)) / (box.x - (crossX)));
    return -(box.y - (crossY)) / (box.x - (crossX));
}

float Bowman::getIntercept()
{
    if (player == 1)
        printf("intercept is %f\n", box.y + box.h / 2 - this->getSlope() * box.x + box.w / 2);
    return (box.y + box.h / 2 - this->getSlope() * box.x + box.w / 2);
}

std::vector<float> Bowman::getX()
{
    std::vector<float> lol;
    lol.push_back(x_pos);
    for (std::vector<Clone>::iterator it = clones.begin(); it != clones.end(); ++it)
    {
        lol.push_back(it->getX());
    }
    return lol;
}

std::vector<float> Bowman::getY()
{
    std::vector<float> lol;
    lol.push_back(y_pos);
    for (std::vector<Clone>::iterator it = clones.begin(); it != clones.end(); ++it)
    {
        lol.push_back(it->getY());
    }
    return lol;
}

void Bowman::hit(std::vector<int> w)
{
    int i;
    std::sort(w.rbegin(), w.rend());

    for (i = 0; i < w.size(); i++)
    {
        // printf("%d ", w.at(i));
        // minus 1 lives if hit, erases clone if hit
        if (w.at(i) > 0)
        {
            clones.erase(clones.begin() + w.at(i) - 1);
            // clones.insert()
            clonesNum--;
        }
        else if (w.at(i) == 0)
        {
            lives--;
            if (lives <= 0)
                clonesNum = 0;
        }
    }
    // printf("\n");
}
