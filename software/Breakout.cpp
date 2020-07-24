#include "Breakout.h"


void Breakout::initialise(Adafruit_SSD1306 *ptrDis, MPU6050Lite *ptrAcc, uint8_t oledAddress, uint8_t mpuAddress){
  _ptrDisplay = ptrDis;
  _ptrAccelerometer = ptrAcc;
  _paddleWidth = _paddleWidthMax;
  _ball.x = _ptrDisplay->width()/2; 
  _ball.y = _ptrDisplay->height()/2;
  _ball.vx = -1;
  _ball.vy = -1;
                  
  DDRB = 0x07;
  PORTB = 0x07;
  if(!_ptrDisplay->begin(SSD1306_SWITCHCAPVCC, oledAddress)) {
    for(;;); // Don't proceed, loop forever
  }
  _start();
  _ptrAccelerometer->initialise(mpuAddress);
}

void Breakout::runGame() {
  _updatePlayerCoordinates();
  _updateBallCoordinates();
  _checkStatus();
  _render();
}

    
void Breakout::_updatePlayerCoordinates() {
  // Interface with the MPU6050 accelerometer and read registers roll and pitch
  int8_t roll, pitch; 
  _ptrAccelerometer->readRegisters();
  roll = _ptrAccelerometer->roll();
  pitch = _ptrAccelerometer->pitch();

  // Limit between [-_angleLimit, _angleLimit]
  if(roll < -_angleLimit)
    roll = -_angleLimit;
  else if(roll > _angleLimit)
    roll = _angleLimit;
    
  if(pitch < -_angleLimit)
    pitch = -_angleLimit;
  else if(pitch > _angleLimit)
    pitch = _angleLimit;
  
  // map measured angles to [x,y] location on the display
  _player.x = map(roll, -_angleLimit, _angleLimit, 0, (_ptrDisplay->width()-_paddleWidth));
  _player.y = map(pitch, _angleLimit, -_angleLimit, 20, (_ptrDisplay->height()-_paddleHeight));
}

// 
void  Breakout::_updateBallCoordinates() {
  coordinates_t temp;
  
  // update ball position
  _ball.x += _ball.vx;
  _ball.y += _ball.vy;

  // update ball velocities (check for wall collisions)
  if( (_ball.x < 0) || (_ball.x > _ptrDisplay->width()) )
    _ball.vx = -_ball.vx;
  if( _ball.y < 0 )
    _ball.vy = -_ball.vy;

  // if the ball reaches the bottom of the screen, reduce the paddle width
  if(_ball.y > _ptrDisplay->height()){
    _paddleWidth -= _paddleWidthIncrement;
    _ball.vy = -_ball.vy;
    PORTB = 0x01;
    // beep(LOOSE);
    tone(10, 1000, 50);
  }

  if( _collisionDetection(&_ball, &_player, &_paddleWidth) ){
    _ball.vy = -_ball.vy;
    PORTB = 0x02;
    tone(10, 3000, 50);
  }

  for(uint8_t j=0; j<LEVEL_HEIGHT; j++)
    for(uint8_t i=0; i<LEVEL_WIDTH; i++){
      if( _level[j][i] )
        temp.x = i * _blockSize;
        temp.y = j * _blockSize;
        if( _collisionDetection(&_ball, &temp, &_blockSize) ){
            _level[j][i] = 0;
          _ball.vx = -_ball.vx;
          _ball.vy = -_ball.vy;
          tone(10, 6000, 50);
        }
    }
}


// Collision detection using Axis-Aligned Bounding Box (AABB) method
bool Breakout::_collisionDetection(coordinates_t *objectA, coordinates_t *objectB, uint8_t *len) {
  bool rtn = false;
  if( (objectA->x >= objectB->x) && (objectA->x <= (objectB->x + *len)) && (objectA->y >= objectB->y) && (objectA->y <= (objectB->y + *len)) )
    rtn = true;
  return rtn;
}



void Breakout::_render(){
  _ptrDisplay->clearDisplay();
  _ptrDisplay->fillRect(_player.x, _player.y, _paddleWidth, _paddleHeight, SSD1306_WHITE);
  _ptrDisplay->drawCircle(_ball.x, _ball.y, 1, SSD1306_WHITE);
  for(uint8_t j=0; j<LEVEL_HEIGHT; j++)
    for(uint8_t i=0; i<LEVEL_WIDTH; i++){
      if( _level[j][i] )
        _ptrDisplay->fillRect(i*_blockSize, j*_blockSize, _blockSize, _blockSize, SSD1306_WHITE);
    }
  _ptrDisplay->display();
  PORTB = 0;
}
  

void Breakout::_checkStatus(){
  if( (_paddleWidth < _paddleWidthMin) || (_paddleWidth > _paddleWidthMax) )
    _gameOver();
  else{
    uint8_t sum = 0;
    for(uint8_t j=0; j<LEVEL_HEIGHT; j++)
      for(uint8_t i=0; i<LEVEL_WIDTH; i++){
        if( _level[j][i] )
          sum++;
      }
    if( sum == 0 )
      _gameWin();   
  }
}


void Breakout::_start() {
  _ptrDisplay->clearDisplay();
  _ptrDisplay->display();
  PORTB = 0x00;
  char msg[62] = {'J','a','k','e',' ','F','r','e','n','c','h',' ','B','E','n','g',',',' ','P','h','D','\n',
                  'E','m','b','e','d','d','e','d',' ','S','o','f','t','w','a','r','e',' ','E','n','g','\n','\n',
                  'T','e','l',':',' ','0','7','7','4','5',' ','6','6','3','8','3','5'};
  _ptrDisplay->clearDisplay();
  _ptrDisplay->setTextSize(1);            
  _ptrDisplay->setTextColor(SSD1306_WHITE);        
  _ptrDisplay->setCursor(0,0);            
  for(int8_t i=0; i<62; i++){

    if( msg[i] == ' ' )
      delay(100);
    else
      tone(10, 7000, 50);
    _ptrDisplay->print(msg[i]);
    _ptrDisplay->display();
    delay(60);  
  }
  delay(3000);
}


void Breakout::_gameWin() {
  for (int i = 0; i-- > -IMAGE_GAMEWIN_W; ){
    _ptrDisplay->clearDisplay();
    _ptrDisplay->drawBitmap(0, i, screenGameWin, IMAGE_GAMEWIN_H, IMAGE_GAMEWIN_W, SSD1306_WHITE);
    _ptrDisplay->display();
      tone(10, -i*50, 5);
  }

  _ptrDisplay->clearDisplay();
  _ptrDisplay->invertDisplay(false);
  _ptrDisplay->drawBitmap(0, 0, screenWinnerCup, IMAGE_GAMEWINCUP_H, IMAGE_GAMEWINCUP_W, SSD1306_WHITE);
  _ptrDisplay->display();
  tone(10, 5000, 500);
  delay(5000);
  _reboot();
}


void Breakout::_gameOver() {
  _ptrDisplay->clearDisplay();
  _ptrDisplay->drawBitmap(27,1, screenGameOver, IMAGE_GAMEOVER_H, IMAGE_GAMEOVER_W, 1);
  for(uint8_t i=0; i<10; i++)
  {
     PORTB = 0x01;
    tone(10, 2000, 50);
    _ptrDisplay->invertDisplay(false);
    _ptrDisplay->display();
    delay(500);
    PORTB = 0x02;
    tone(10, 1000, 50);
    _ptrDisplay->invertDisplay(true);
    _ptrDisplay->display();
    delay(500);
  }
  _reboot();
}


void Breakout::_reboot(){
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {}
}
