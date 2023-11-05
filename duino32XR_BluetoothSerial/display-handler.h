#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H

// SH1106 based 128x64 pixel OLED display with SPI/I2C interface
// https://github.com/rene-mt/esp8266-oled-sh1106/tree/master
#include "SH1106.h"


extern SH1106   display;
extern int      showType;      // Current type of LED-State (color)
extern int      bright  ;      // Current Brightness of LEDs


void updateDisplay();
void updateDisplay2(int old, int newBright);

#endif
