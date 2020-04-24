#pragma once
#include "SpaceInvadersBase.h"
#include "types.h"

// Derived class "Missile", also a sprite and has a specific form/shape, and specific (x,y) derived from input sprite
// also has a simple way of moving
class Missile : public Sprite
{
public:
    Missile();
    void setMissileDirection(direction_t dir);
    virtual void Move();

private:
    direction_t direction;
};

