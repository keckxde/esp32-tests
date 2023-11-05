#include "bluetooth-handler.h"


BluetoothHandler BTHandler(0);
//boolean confirmRequestPending = true;


BluetoothHandler::BluetoothHandler(uint8_t uart_nr = 0) {
  Serial.printf("BluetoothHandler::BluetoothHandler %d", uart_nr);
}

void BluetoothHandler::begin() {
  Serial.printf("BluetoothHandler::begin ");

  //SerialBT.enableSSP();
  //SerialBT.onConfirmRequest(this->*BTConfirmRequestCallback);
  //SerialBT.onAuthComplete(this->*BTAuthCompleteCallback);
  SerialBT.begin("ESP32test");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void BluetoothHandler::loop() {
  //Serial.printf("BluetoothHandler::loop ");
  if (confirmRequestPending) {
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
}


void BluetoothHandler::BTConfirmRequestCallback(uint32_t numVal) {
  Serial.printf("BluetoothHandler::BTConfirmRequestCallback %d ", numVal);
  confirmRequestPending = true;
  Serial.println(numVal);
}

void BluetoothHandler::BTAuthCompleteCallback(boolean success) {
  Serial.printf("BluetoothHandler::BTAuthCompleteCallback %d ", success);
  confirmRequestPending = false;
  if (success) {
    Serial.println("Pairing success!!");
  } else {
    Serial.println("Pairing failed, rejected by user!!");
  }
}