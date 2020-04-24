#include "SpaceInvadersMissile.h"
#include "Sprites.h"


Missile::Missile() : Sprite(&spaceMissile[0], 0, 0)
{
    direction = DOWN;
}


void Missile::setMissileDirection(direction_t dir)
{
    direction = dir;
}


void Missile::Move()
{
    if (direction == DOWN)
        y = y + 3;
    else
        y = y - 3;


    if ((y > SCREENHEIGHTMAX) || (y < SCREENHEIGHTMIN))
    {
        setEnergy(0);
        setStatus(0);
    }
    Render();
}