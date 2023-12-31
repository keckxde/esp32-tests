#ifndef SHOW_PIXEL_HANDLER_H
#define SHOW_PIXEL_HANDLER_H

// Adafruit NeoPixel - could handle strips with many Pixels
// https://github.com/adafruit/Adafruit_NeoPixel
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 12   // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 1  // Only One neopixel


class ShowPixelHandler {

public:
  int type = 0;
  int type_d = 0;
  int bright = 0;
  int bright_d = 0;
  // Parameter 1 = number of pixels in strip,  neopixel stick has 8
  // Parameter 2 = pin number (most are valid)
  // Parameter 3 = pixel type flags, add together as needed:
  //   NEO_RGB     Pixels are wired for RGB bitstream
  //   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
  //   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
  //   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
  Adafruit_NeoPixel *strip;
  //  = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);



  ShowPixelHandler(uint8_t count, uint8_t pin, uint8_t options) {
    strip = new Adafruit_NeoPixel(count, pin, options);
  }

  void begin() {
    strip->begin();
    strip->show();  // Initialize all pixels to 'off'
  }

  void loop() {
    //Serial.printf("ButtonHandler::loop ");
    if (type_d != type || bright_d != bright) {
      Serial.printf("ShowPixelHandler::loop Changing Type %d, Brightness %d\n",type,bright);
      startShow(type, bright);
      type_d = type;
      bright_d = bright;
    }
  }

  void startShow(int i,int brightness) {
    strip->setBrightness(brightness);
    switch (i) {
      case 0:
        colorWipe(strip->Color(0, 0, 0), 50);  // Black/off
        break;
      case 1:
        colorWipe(strip->Color(255, 0, 0), 50);  // Red
        break;
      case 2:
        colorWipe(strip->Color(0, 255, 0), 50);  // Green
        break;
      case 3:
        colorWipe(strip->Color(0, 0, 255), 50);  // Blue
        break;
      case 4:
        theaterChase(strip->Color(127, 127, 127), 50);  // White
        break;
      case 5:
        theaterChase(strip->Color(127, 0, 0), 50);  // Red
        break;
      case 6:
        theaterChase(strip->Color(0, 0, 127), 50);  // Blue
        break;
        /*
    case 7: rainbow(20);
            break;
    case 8: rainbowCycle(20);
            break;
    case 9: theaterChaseRainbow(50);
            break;*/
    }
  }

  // Fill the dots one after the other with a color
  void colorWipe(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, c);
      strip->show();
      delay(wait);
    }
  }

  void rainbow(uint8_t wait) {
    uint16_t i, j;

    for (j = 0; j < 256; j++) {
      for (i = 0; i < strip->numPixels(); i++) {
        strip->setPixelColor(i, Wheel((i + j) & 255));
      }
      strip->show();
      delay(wait);
    }
  }

  // Slightly different, this makes the rainbow equally distributed throughout
  void rainbowCycle(uint8_t wait) {
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++) {  // 5 cycles of all colors on wheel
      for (i = 0; i < strip->numPixels(); i++) {
        strip->setPixelColor(i, Wheel(((i * 256 / strip->numPixels()) + j) & 255));
      }
      strip->show();
      delay(wait);
    }
  }

  //Theatre-style crawling lights.
  void theaterChase(uint32_t c, uint8_t wait) {
    for (int j = 0; j < 10; j++) {  //do 10 cycles of chasing
      for (int q = 0; q < 3; q++) {
        for (int i = 0; i < strip->numPixels(); i = i + 3) {
          strip->setPixelColor(i + q, c);  //turn every third pixel on
        }
        strip->show();

        delay(wait);

        for (int i = 0; i < strip->numPixels(); i = i + 3) {
          strip->setPixelColor(i + q, 0);  //turn every third pixel off
        }
      }
    }
  }

  //Theatre-style crawling lights with rainbow effect
  void theaterChaseRainbow(uint8_t wait) {
    for (int j = 0; j < 256; j++) {  // cycle all 256 colors in the wheel
      for (int q = 0; q < 3; q++) {
        for (int i = 0; i < strip->numPixels(); i = i + 3) {
          strip->setPixelColor(i + q, Wheel((i + j) % 255));  //turn every third pixel on
        }
        strip->show();

        delay(wait);

        for (int i = 0; i < strip->numPixels(); i = i + 3) {
          strip->setPixelColor(i + q, 0);  //turn every third pixel off
        }
      }
    }
  }

  // Input a value 0 to 255 to get a color value.
  // The colours are a transition r - g - b - back to r.
  uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
      return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170) {
      WheelPos -= 85;
      return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
};


#endif