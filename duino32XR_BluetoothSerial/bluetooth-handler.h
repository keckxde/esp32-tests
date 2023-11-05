#include "Arduino.h"
#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// https://github.com/Uberi/Arduino-CommandParser
#include <CommandParser.h>

typedef CommandParser<> MyCommandParser;


class BluetoothHandler{
  public:

    boolean confirmRequestPending = true;
    BluetoothSerial SerialBT;
    MyCommandParser parser;

    BluetoothHandler(uint8_t uart_nr);
    void begin();
    void loop();
    void BTConfirmRequestCallback(uint32_t numVal);
    void BTAuthCompleteCallback(boolean success);


};


extern BluetoothHandler BTHandler;

#endif
