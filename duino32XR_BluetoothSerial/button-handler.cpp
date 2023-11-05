#include "esp32-hal-gpio.h"
#include "button-handler.h"

ButtonHandler::ButtonHandler(uint8_t pinLeft, uint8_t pinMiddle, uint8_t pinRight)
  : pinLeft(pinLeft),
    pinMiddle(pinMiddle),
    pinRight(pinRight) {

  buttonRIGHT = NULL;
  buttonLEFT = NULL;
  buttonCENTER = NULL;

  
  Serial.printf("ButtonHandler::ButtonHandler %d, %d, %d", pinLeft, pinMiddle, pinRight);
}

void ButtonHandler::begin() {
  Serial.printf("ButtonHandler::begin ");

  pinMode(pinLeft, INPUT_PULLDOWN);
  pinMode(pinMiddle, INPUT_PULLUP);
  pinMode(pinRight, INPUT_PULLUP);


  // Initialize the Button OBjects with the correlated PINs
  buttonLEFT = new Button(pinLeft);  
  buttonLEFT->begin();
  buttonRIGHT = new Button(pinRight); 
  buttonRIGHT->begin();
  buttonCENTER = new Button(pinMiddle);
  buttonCENTER->begin();
}

void ButtonHandler::loop() {
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
