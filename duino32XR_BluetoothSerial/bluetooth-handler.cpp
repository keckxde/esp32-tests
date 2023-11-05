#include "bluetooth-handler.h"

#include "show-button-handler.h"
extern ShowButtonHandler Buttons;

void cmd_bright(MyCommandParser::Argument *args, char *response) {
  Serial.print("BRIGHT int: ");
  int val = atoi(args[0].asString);
  Serial.println(val);
  strlcpy(response, "success", MyCommandParser::MAX_RESPONSE_SIZE);

  Buttons.bright = val;
}

void cmd_brightinc(MyCommandParser::Argument *args, char *response) {
  Serial.print("BRIGHTINC int: ");
  int val = atoi(args[0].asString);
  Serial.println(val);
  strlcpy(response, "success", MyCommandParser::MAX_RESPONSE_SIZE);

  Buttons.bright += val;
  Buttons.bright %= 255;
}

void cmd_typ(MyCommandParser::Argument *args, char *response) {
  Serial.print("TYP int: ");
  int val = atoi(args[0].asString);
  Serial.println(val);
  strlcpy(response, "success", MyCommandParser::MAX_RESPONSE_SIZE);

  Buttons.type = val;
}

void cmd_typinc(MyCommandParser::Argument *args, char *response) {
  Serial.print("TYPINC int: ");
  int val = atoi(args[0].asString);
  Serial.println(val);
  strlcpy(response, "success", MyCommandParser::MAX_RESPONSE_SIZE);

  Buttons.type += val;
  Buttons.type %= 7;
}

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

  //parser.registerCommand("TEST", "s", &cmd_test);
  parser.registerCommand("BRIGHT", "s", &cmd_bright);
  parser.registerCommand("BRIGHTINC", "s", &cmd_brightinc);
  parser.registerCommand("TYP", "s", &cmd_typ);
  parser.registerCommand("TYPINC", "s", &cmd_typinc);

}

void BluetoothHandler::loop() {
  //Serial.printf("BluetoothHandler::loop ");
  /*if (confirmRequestPending) {
    if (Serial.available()) {
      int dat = Serial.read();
      if (dat == 'Y' || dat == 'y') {
        SerialBT.confirmReply(true);
      } else {
        SerialBT.confirmReply(false);
      }
    }
  } else */

  char line[128];
  char response[MyCommandParser::MAX_RESPONSE_SIZE];
      

  if (SerialBT.available()) {
    size_t lineLength = SerialBT.readBytesUntil('\n', line, 127);
    line[lineLength] = '\0';

    parser.processCommand(line, response);

    Serial.printf("Command: %s, Response: %s\n",line,response);
    
    SerialBT.printf("Response: %s",response);
    
  }
  delay(20);
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