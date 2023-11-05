#include "Arduino.h"
#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

// Simple Button Library - that can handle Pressed/Released Functions for Buttons:
// https://github.com/madleech/Button
#include <Button.h>



class ButtonHandler{
  public:
    uint8_t pinLeft   = 55;
    uint8_t pinMiddle = 1;
    uint8_t pinRight  = 2;
    
    // Initialize the Button OBjects with the correlated PINs
    Button *buttonRIGHT;//(BUTTON_PRESS_PIN);   // Connect your button between pin 2 and GND
    Button *buttonLEFT;//(BUTTON_LEFT_PIN);     // Connect your button between pin 3 and GND
    Button *buttonCENTER;//(BUTTON_RIGHT_PIN);  // Connect your button between pin 4 and GND
        

    ButtonHandler(uint8_t pinLeft,uint8_t pinMiddle,uint8_t pinRight);
    void begin();
    void loop();
};

#endif
