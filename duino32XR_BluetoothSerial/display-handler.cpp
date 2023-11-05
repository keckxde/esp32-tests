#include "display-handler.h"


// For I2C display: create the display object connected to pin SDA and SDC
// SH1106(int i2cAddress, int sda, int sdc);
#define I2C_OLED_ADRESS   0x3c
#define I2C_OLED_PIN_SDA  14
#define I2C_OLED_PIN_SDC  27

SH1106 display(I2C_OLED_ADRESS, I2C_OLED_PIN_SDA, I2C_OLED_PIN_SDC);



void updateDisplay() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  delay(10);
  display.clear();
  display.drawString(30, 0, "SCNT");
  display.setFont(ArialMT_Plain_10);

  char buffer[26];
  sprintf(buffer, "But RIGHT: Brightness %3d", bright);
  Serial.println(buffer);
  display.drawString(0, 16, "But CENTER: RGB");
  display.drawString(0, 32, "But LEFT: Sound One");
  display.drawString(0, 48, buffer);
  display.display();
}


void updateDisplay2(int old, int newBright) {
  display.setFont(ArialMT_Plain_10);
  char buffer[26];
  sprintf(buffer, "But RIGHT: Brightness %3d", old);
  display.setColor(BLACK);
  display.drawString(0, 48, buffer);
  display.display();

  display.setColor(WHITE);
  sprintf(buffer, "But RIGHT: Brightness %3d", newBright);
  display.drawString(0, 48, buffer);
  display.display();

  Serial.println(buffer);
}