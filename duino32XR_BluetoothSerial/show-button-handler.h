#ifndef SHOW_BUTTON_HANDLER_H
#define SHOW_BUTTON_HANDLER_H
#include "button-handler.h"


class ShowButtonHandler : public ButtonHandler {

public:
  int type = 0;
  int bright = 0;

  ShowButtonHandler(uint8_t pinLeft, uint8_t pinMiddle, uint8_t pinRight)
    : ButtonHandler(pinLeft, pinMiddle, pinRight) {}

  void loop() {
    //Serial.printf("ButtonHandler::loop ");
    if (buttonRIGHT->read() == Button::PRESSED) {
      Serial.println("ShotButtonHandler Right pressed");
      simBrightnessDown();
      delay(5);
    }

    if (buttonLEFT->read() == Button::PRESSED) {
      Serial.println("ShotButtonHandler Left pressed");
      simBrightnessUp();
      delay(5);
    }

    if (buttonCENTER->released()) {
      Serial.println("ShotButtonHandler Button Center released");
      simType();
    }
  }

  void simBrightnessUp() {
    bright++;
    if (bright >= 255) {
      bright = 0;
    }
  }

  void simBrightnessDown() {
    bright--;
    if (bright <= 0) {
      bright = 255;
    }
  }

  void simType() {
    type++;
    if (type > 6)
      type = 1;
  }
};


#endif