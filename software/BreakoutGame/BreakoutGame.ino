#include "Breakout.h"

#define OLED_ADDRESS    0x3c  // Reset pin # (or -1 if sharing Arduino reset pin)
#define MPU_ADDRESS     0x68  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH    128   // OLED display width, in pixels
#define SCREEN_HEIGHT   32    // OLED display height, in pixels
#define OLED_RESET      4     // Reset pin # (or -1 if sharing Arduino reset pin)

MPU6050Lite mpu;
Breakout breakout;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  breakout.initialise(&display, &mpu, OLED_ADDRESS, MPU_ADDRESS);    
}


void loop() {
  breakout.runGame();
}
