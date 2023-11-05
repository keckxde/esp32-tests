

// My own handlers
#include "display-handler.h"
#include "show-button-handler.h"
#include "show-pixel-handler.h"

#define BLUETOOTH
//#define WIFI
#ifdef BLUETOOTH
#include "bluetooth-handler.h"
#endif
#ifdef WIFI
#include <WiFi.h>
#endif

// I/O  Settings as defined with DSTRIK D-duino32 XR:
#define BUTTON_PRESS_PIN 15
#define BUTTON_LEFT_PIN 2
#define BUTTON_RIGHT_PIN 13

#define BUZZER 4

// https://github.com/Uberi/Arduino-CommandParser
#include <CommandParser.h>

typedef CommandParser<> MyCommandParser;

ShowButtonHandler Buttons = ShowButtonHandler(BUTTON_LEFT_PIN, BUTTON_PRESS_PIN, BUTTON_RIGHT_PIN);
DisplayHandler Display = DisplayHandler(I2C_OLED_ADRESS, I2C_OLED_PIN_SDA, I2C_OLED_PIN_SDC);
ShowPixelHandler Pixel = ShowPixelHandler(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

#ifdef WIFI
const char* ssid = "ESP32 WiFI AP"; /*Set Your SSID*/
const char* password = "123456789"; /*Set Your Password*/

WiFiServer server(80); /* Instance of WiFiServer with port number 80 */
WiFiClient client;
IPAddress Ip(192, 168, 1, 1);
IPAddress NMask(255, 255, 255, 0);
#endif


void setup() {
  Serial.begin(115200);

  while (!Serial)
    ;

  Buttons.begin();
  Display.begin();
  Pixel.begin();


  Serial.print("ESP32 SDK: ");
  Serial.println(ESP.getSdkVersion());

#ifdef BLUETOOTH
  BTHandler.begin();
#endif
#ifdef WIFI
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  delay(100);
  WiFi.softAPConfig(Ip, Ip, NMask);
  Serial.print(F("Connect to IP address: "));
  Serial.println(WiFi.softAPIP());
  server.begin();
#endif
}

#ifdef WIFI
void html() {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  client.println("<style>");
  client.println("html { font-family: Roboto; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button {background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;");
  client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}");
  client.println(".button_ON {background-color: white; color: black; border: 2px solid #4CAF50;}");
  client.println(".button_OFF {background-color: white; color: black; border: 2px solid #f44336;}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h2>ESP32 WiFi AP Mode</h2>");
  client.println("<p>Click to ON and OFF the LED</p>");
  String typ = String("Typ: ") + String(Buttons.type) + String(" Brightness: ") + String(Buttons.bright);
  client.println("<p>" + typ + "</p>");
  client.print("<p><a href=\"/BRIGHTINC\n\"><button class=\"button button_ON\">BRIGHTINC</button></a></p>"); 
  client.print("<p><a href=\"/TYPINC\n\"><button class=\"button button_ON\">TYPINC</button></a></p>"); 

  client.println("</body>");
  client.println("</html>");
  client.flush();
}

#endif


void loop() {

  Buttons.loop();
  Display.brightness = Buttons.bright;
  Display.type = Buttons.type;

  Pixel.bright = Buttons.bright;
  Pixel.type = Buttons.type;

  Display.loop();
  Pixel.loop();

#ifdef BLUETOOTH
  BTHandler.loop();
  delay(25);
#endif
#ifdef WIFI
  String request;
  client = server.available();
  if (!client) {
    return;
  }
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      request += c;

      if (c == '\n') {
        if (request.indexOf("GET /BRIGHTINC") != -1) {
          Serial.println("BRIGHTINC in ON");
          Buttons.bright += 10;
        }else if (request.indexOf("GET /TYPINC") != -1) {
          Serial.println("TYPINC in ON");
          Buttons.type += 1;
          Buttons.type %= 7;
        }
        
        html();
        break;
      }
    }
  }
#endif
}