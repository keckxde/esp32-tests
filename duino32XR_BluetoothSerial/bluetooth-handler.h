#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include "BluetoothSerial.h"
extern BluetoothSerial SerialBT;
extern boolean confirmRequestPending;


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


void BTConfirmRequestCallback(uint32_t numVal);
void BTAuthCompleteCallback(boolean success);


#endif
