#include "display-handler.h"



DisplayHandler::DisplayHandler(uint8_t i2c_oled_adress, uint8_t pinSDA, uint8_t pinSDC)
  : i2c_oled_adress(i2c_oled_adress),
    pinSDA(pinSDA),
    pinSDC(pinSDC) {

  display = new SH1106(I2C_OLED_ADRESS, I2C_OLED_PIN_SDA, I2C_OLED_PIN_SDC);

  Serial.printf("DisplayHandler::DisplayHandler %d, %d, %d", i2c_oled_adress, pinSDA, pinSDC);
}

void DisplayHandler::begin() {
  Serial.printf("DisplayHandler::begin ");

  // Initialize the Button OBjects with the correlated PINs
  display->init();
  //display->flipScreenVertically();
  display->setFont(ArialMT_Plain_10);
  delay(10);
  display->clear();
  display->drawString(30, 0, "ESP32-DEMO");
  display->setFont(ArialMT_Plain_10);

  //display->drawString(0, 16, "But CENTER: RGB");
  display->drawString(0, 32, "Visualisation Type:");
  display->drawString(0, 48, "Brightness:        ");
  display->display();

}

void DisplayHandler::loop() {

  char buffer[4];
  if (brightness_d != brightness) {
    display->setFont(ArialMT_Plain_10);
    
    sprintf(buffer, "%3d", brightness_d);
    display->setColor(BLACK);
    display->drawString(100, 48, buffer);
    display->display();

    display->setColor(WHITE);
    sprintf(buffer, "%3d", brightness);
    display->drawString(100, 48, buffer);
    display->display();

    brightness_d = brightness;
  }
  if (type_d != type) {
    display->setFont(ArialMT_Plain_10);
    
    sprintf(buffer, "%3d", type_d);
    display->setColor(BLACK);
    display->drawString(100, 32, buffer);
    display->display();

    display->setColor(WHITE);
    sprintf(buffer, "%3d", type);
    display->drawString(100, 32, buffer);
    
    display->display();

    type_d = type;
  }
}