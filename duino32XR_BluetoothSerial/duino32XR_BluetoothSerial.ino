

// My own bluetooth-handler
#include "display-handler.h"
#include "bluetooth-handler.h"
#include "show-button-handler.h"
#include "show-pixel-handler.h"

// I/O  Settings as defined with DSTRIK D-duino32 XR:
#define BUTTON_PRESS_PIN 15
#define BUTTON_LEFT_PIN 2
#define BUTTON_RIGHT_PIN 13

#define BUZZER 4



// GLOBAL VARIABLES to store states
int showType = 0;  // Current type of LED-State (color)
int bright = 0;    // Current Brightness of LEDs

ShowButtonHandler Buttons = ShowButtonHandler(BUTTON_LEFT_PIN, BUTTON_PRESS_PIN, BUTTON_RIGHT_PIN);
DisplayHandler Display = DisplayHandler(I2C_OLED_ADRESS, I2C_OLED_PIN_SDA, I2C_OLED_PIN_SDC);
ShowPixelHandler Pixel = ShowPixelHandler(PIXEL_COUNT,PIXEL_PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  Serial.begin(115200);

  Buttons.begin();
  Display.begin();
  Pixel.begin();
  

  Serial.print("ESP32 SDK: ");
  Serial.println(ESP.getSdkVersion());

  BTHandler.begin();
}


void loop() {

  Buttons.loop();
  Display.brightness = Buttons.bright;
  Display.type = Buttons.type;
  
  Pixel.bright = Buttons.bright;
  Pixel.type = Buttons.type;
  
  Display.loop();
  Pixel.loop();
  
  BTHandler.loop();

  delay(25);
}

void soundone() {
  unsigned char i, j;

  for (i = 0; i < 5; i++)

  {

    for (i = 0; i < 200; i++)

    {

      digitalWrite(BUZZER, HIGH);

      delay(1);  //Change this could adjust voice

      digitalWrite(BUZZER, LOW);

      delay(1);
    }

    for (i = 0; i < 100; i++)

    {
      digitalWrite(BUZZER, HIGH);

      delay(2);

      digitalWrite(BUZZER, LOW);

      delay(2);
    }
  }
}


