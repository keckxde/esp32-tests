#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H

// SH1106 based 128x64 pixel OLED display with SPI/I2C interface
// https://github.com/rene-mt/esp8266-oled-sh1106/tree/master
#include "SH1106.h"

// For I2C display: create the display object connected to pin SDA and SDC
// SH1106(int i2cAddress, int sda, int sdc);
#define I2C_OLED_ADRESS 0x3c
#define I2C_OLED_PIN_SDA 14
#define I2C_OLED_PIN_SDC 27


class DisplayHandler {
public:
  SH1106 *display;
  uint8_t i2c_oled_adress = 1;
  uint8_t pinSDA = 2;
  uint8_t pinSDC = 3;
  
  // Initialize the Button OBjects with the correlated PINs
  int brightness = 0;
  int brightness_d = -1;

  int type = 0;
  int type_d = -1;

  DisplayHandler(uint8_t i2c_oled_adress, uint8_t pinSDA, uint8_t pinSDC);
  void begin();
  void loop();
};

#endif
