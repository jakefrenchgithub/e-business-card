// Sprite constructor
Sprite::Sprite(uint8_t* const spritePtr, uint8_t xStart, uint8_t yStart)
{
    energyLevel = 1;
    Ammo = 1;
    x = xStart;
    y = yStart;
    imagePtr = spritePtr;
}


// Sprite constructor
void Sprite::Render()
{
    if (Status) 
        display.drawBitmap(x, y, imagePtr, 5, 6, BLACK); 
}

