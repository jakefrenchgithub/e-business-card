/*********************************************************************************************************/
/*!
  @file     Breakout.h
  Library by J. French https://github.com/jakefrenchgithub/e-business-card, released to the public domain
  License: MIT, https://opensource.org/licenses/MIT

  This is a basic library that mimics the 1976 game, Breakout worked on by Steve Wozniak and Steve Jobs.
  The Breakout game had influenced Wozniak's design for the Apple II computer, including game paddle,
  color graphics circuitry, sound and graphics commands in BASIC.

  Instead of a hwardware paddle this library uses the MPU6050 accelerometer for measuring roll & pitch,
  which are then mapped to 2D coordinates on the OLED display. 

  Supporting documentation
  MPU6050Lite library:  https://github.com/jakefrenchgithub/MPU6050Lite
  Background: https://en.wikipedia.org/wiki/Breakout_(video_game)
  
  J. French, 24/7/20
*/
/*********************************************************************************************************/

#ifndef BREAKOUT_h
#define BREAKOUT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "screenImages.h"
#include <MPU6050Lite.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/wdt.h>

#define LEVEL_HEIGHT 3
#define LEVEL_WIDTH  32

typedef struct 
{
    int8_t x, y, vx, vy;
} coordinates_t;

enum turn{
  PLAYER_AND_BALL,
  BLOCK_AND_BALL,
};
   
class Breakout
{
public:
    void initialise(Adafruit_SSD1306 *ptrDis, MPU6050Lite *ptrAcc, uint8_t oledAddress, uint8_t mpuAddress);      
    void runGame();
    
private:
    void _updatePlayerCoordinates();
    void _updateBallCoordinates();    
    void _checkStatus();   
    bool _collisionDetection(coordinates_t *objectA, coordinates_t *objectB, uint8_t *len);
    void _render();
    void _start();
    void _gameWin();    
    void _gameOver();
    void _reboot();
    Adafruit_SSD1306 *_ptrDisplay;
    MPU6050Lite *_ptrAccelerometer;
    coordinates_t _ball, _player;
    uint8_t _paddleWidth, _blockSize = 4;
    uint8_t const _paddleHeight = 2, _angleLimit = 25, _paddleWidthMax = 20, _paddleWidthMin = 2, _paddleWidthIncrement = 5;
                  
    uint8_t _level[LEVEL_HEIGHT][LEVEL_WIDTH] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

};


#endif
