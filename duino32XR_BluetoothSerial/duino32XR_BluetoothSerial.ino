// Adafruit NeoPixel - could handle strips with many Pixels
// https://github.com/adafruit/Adafruit_NeoPixel
#include <Adafruit_NeoPixel.h>

// Simple Button Library - that can handle Pressed/Released Functions for Buttons:
// https://github.com/madleech/Button
#include <Button.h>

// My own bluetooth-handler
#include "display-handler.h"
#include "bluetooth-handler.h"

// I/O  Settings as defined with DSTRIK D-duino32 XR:
#define BUTTON_PRESS_PIN  15
#define BUTTON_LEFT_PIN   2
#define BUTTON_RIGHT_PIN  13

#define PIXEL_PIN     12          // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT   1         // Only One neopixel
#define BUZZER        4

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Initialize the Button OBjects with the correlated PINs
Button buttonRIGHT(BUTTON_PRESS_PIN);   // Connect your button between pin 2 and GND
Button buttonLEFT(BUTTON_LEFT_PIN);     // Connect your button between pin 3 and GND
Button buttonCENTER(BUTTON_RIGHT_PIN);  // Connect your button between pin 4 and GND

// GLOBAL VARIABLES to store states
int   showType    = 0;      // Current type of LED-State (color)
int   bright      = 0;      // Current Brightness of LEDs

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PRESS_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  buttonRIGHT.begin();
  buttonLEFT.begin();
  buttonCENTER.begin();

  updateDisplay();

  strip.begin();
  strip.show();  // Initialize all pixels to 'off'

  Serial.print("ESP32 SDK: ");
  Serial.println(ESP.getSdkVersion());
  Serial.begin(115200);
  
  SerialBT.enableSSP();
  SerialBT.onConfirmRequest(BTConfirmRequestCallback);
  SerialBT.onAuthComplete(BTAuthCompleteCallback);
  SerialBT.begin("ESP32test");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}


void loop() {

  if (buttonRIGHT.read() == Button::PRESSED) {
    //    Serial.println("Button 1 pressed");
    brightness();
    //soundtwo();
  }
  if (buttonRIGHT.released()) {
    Serial.println("Button 1 released");
    //onButton();
    updateDisplay();
  }

  if (buttonLEFT.released()) {
    Serial.println("Button 2 released");
    soundone();
  }

  if (buttonCENTER.released()) {
    showType++;
    if (showType > 6)
      showType = 1;
    startShow(showType);
  }

  /*if (confirmRequestPending) {
    if (Serial.available()) {
      int dat = Serial.read();
      if (dat == 'Y' || dat == 'y') {
        SerialBT.confirmReply(true);
      } else {
        SerialBT.confirmReply(false);
      }
    }
  } else {
    if (Serial.available()) {
      SerialBT.write(Serial.read());
    }
    if (SerialBT.available()) {
      Serial.write(SerialBT.read());
    }
    delay(20);
  }
*/
  //UA_Server_run_iterate(server, false);
  /*UA_Server_run_iterate(server, false);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  //   ESP_ERROR_CHECK(esp_task_wdt_reset());
  taskYIELD();
*/
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
void brightness() {
  int old = bright;
  bright = bright - 1;
  if (bright <= 0) {
    bright = 64;
  }

  updateDisplay2(old, bright);
  delay(100);
}

void soundtwo() {
  unsigned char i, j;

  for (i = 0; i < 5; i++)

  {

    for (i = 0; i < 100; i++)

    {

      digitalWrite(BUZZER, HIGH);

      delay(2);  //Change this could adjust voice

      digitalWrite(BUZZER, LOW);

      delay(2);
    }

    for (i = 0; i < 200; i++)

    {
      digitalWrite(BUZZER, HIGH);

      delay(1);

      digitalWrite(BUZZER, LOW);

      delay(1);
    }
  }
}
void startShow(int i) {
  switch (i) {
    case 0:
      colorWipe(strip.Color(0, 0, 0), 50);  // Black/off
      break;
    case 1:
      colorWipe(strip.Color(255, 0, 0), 50);  // Red
      break;
    case 2:
      colorWipe(strip.Color(0, 255, 0), 50);  // Green
      break;
    case 3:
      colorWipe(strip.Color(0, 0, 255), 50);  // Blue
      break;
    case 4:
      colorWipe(strip.Color(127, 127, 127), 50);  // Blue
      break;
    case 5:
      colorWipe(strip.Color(127, 0, 0), 50);  // Blue
      break;
    case 6:
      colorWipe(strip.Color(0, 0, 127), 50);  // Blue
      break;
    case 7:
      colorWipe(strip.Color(0, 0, 255), 50);  // Blue
      break;
      /*
    case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
            break;
    case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
            break;
    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
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
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    int b = strip.getBrightness();
    strip.setBrightness(bright);
    Serial.printf("Brighness before %d, after %d\n", b, bright);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) {  // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) {  //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);  //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {  // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel((i + j) % 255));  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);  //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}