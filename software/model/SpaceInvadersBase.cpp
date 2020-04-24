#include "SpaceInvadersBase.h"
#include "types.h"

// Sprite constructor
Sprite::Sprite(uint8_t* const spritePtrIn, uint8_t xIn, uint8_t yIn)
{
    alive = true;
    energyLevel = 1;
    ammoLevel = 1;
    x = xIn;
    y = yIn;
    spritePtr = spritePtrIn;
};

// Render function
void Sprite::Render()
{
    //if(Alive)
    //    display.drawBitmap(x, y, spacePtr, 5, 6, BLACK);
}

// retrieve x coordinate 
uint8_t Sprite::getX()
{   
    return x;   
}

// retrieve y coordinate 
uint8_t Sprite::getY()
{   
    return y;   
}

// retrieve Ammo value
uint8_t Sprite::getAmmo()
{   
    return ammoLevel;   
}

// retrieve energyLevel
uint8_t Sprite::getEnergy()
{   
    return energyLevel; 
}

// retrieve status
bool Sprite::getStatus()
{   
    return alive;
}



// set coordinates
void Sprite::setCoord(uint8_t setx, uint8_t sety)
{
    x = setx;
    y = sety;
}

// set energy level coordinates
void Sprite::setEnergy(uint8_t energy)
{
    energyLevel = energy;
}

// set energy level coordinates
void Sprite::setStatus(bool status)
{
    alive = status;
}

// set energy level coordinates
void Sprite::setAmmo(uint8_t ammo)
{
    ammoLevel = ammo;
}