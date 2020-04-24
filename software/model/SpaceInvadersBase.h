#pragma once
#include "types.h"



// Bass class - has a form/shape, x and y position 
// also has a method of moving, though its not defined what this is (virtual)
class Sprite
{
public:
    Sprite(uint8_t* const spritePtrIn, uint8_t xIn, uint8_t yIn);
    virtual void Move() = 0;
    void Render();
    uint8_t getX();
    uint8_t getY();
    uint8_t getAmmo();
    uint8_t getEnergy();
    bool    getStatus();

    void setCoord(uint8_t setx, uint8_t sety);
    void setAmmo(uint8_t ammo);
    void setEnergy(uint8_t energy);
    void setStatus(bool status);

protected:
    bool alive;
    uint8_t* spritePtr;
    uint8_t x, y, ammoLevel, energyLevel;
};