#include "button-handler.h"

ButtonHandler::ButtonHandler(uint8_t pinLeft, uint8_t pinMiddle, uint8_t pinRight)
  : pinLeft(pinLeft),
    pinMiddle(pinMiddle),
    pinRight(pinRight) {

  buttonRIGHT = NULL;
  buttonLEFT = NULL;
  buttonCENTER = NULL;

  pinMode(pinLeft, INPUT_PULLUP);
  pinMode(pinMiddle, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);

  Serial.printf("ButtonHandler::ButtonHandler %d, %d, %d", pinLeft, pinMiddle, pinRight);
}

void ButtonHandler::begin() {
  Serial.printf("ButtonHandler::begin ");

  // Initialize the Button OBjects with the correlated PINs
  buttonRIGHT = new Button(pinRight); 
  buttonRIGHT->begin();
  buttonLEFT = new Button(pinLeft);  
  buttonLEFT->begin();
  buttonCENTER = new Button(pinMiddle);
  buttonCENTER->begin();
}

void ButtonHandler::loop() {
  //Serial.printf("ButtonHandler::loop ");
  if (buttonRIGHT->read() == Button::PRESSED) {
    Serial.println("Button Right pressed");
    // brightness();
  }
  if (buttonRIGHT->released()) {
    Serial.println("Button Right released");
  }

  if (buttonLEFT->released()) {
    Serial.println("Button Left released");
  }

  if (buttonCENTER->released()) {
    Serial.println("Button Center released");
  }
}
