#include "Arduino.h"
#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


class BluetoothHandler{
  public:
    int x = 1;
    int y = 2;
    boolean confirmRequestPending = true;
    BluetoothSerial SerialBT;

    BluetoothHandler(uint8_t uart_nr);
    void begin();
    void loop();
    void BTConfirmRequestCallback(uint32_t numVal);
    void BTAuthCompleteCallback(boolean success);


};


//extern BluetoothSerial SerialBT;
//extern boolean confirmRequestPending;
extern BluetoothHandler BTHandler;

#endif
