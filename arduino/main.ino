#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1015.h>
#include <DFRobot_ESP_EC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
 
#define ONE_WIRE_BUS 13
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DFRobot_ESP_EC ec;
Adafruit_ADS1115 ads;
 
float voltage, ecValue, temperature = 25;
 

String apiKey = "36ZLI26PUVE12HOB";

const char *ssid = "iQOO Z5";
const char *pass = "adityabansal";
const char *server = "api.thingspeak.com";

WiFiClient client;
 
 
void setup()
{
  Serial.begin(115200);
  EEPROM.begin(32);
  ec.begin();
  sensors.begin();
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Drinking Water"));
  display.println(F("Quality Monitoring"));
  display.println(F("System"));
  display.display();

  delay(2000);
  display.clearDisplay();

  Serial.println("Connecting to ");
  Serial.println(ssid);
 
 
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting ...");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
 
 
void loop()
{
  voltage = analogRead(A0);
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  ecValue = ec.readEC(voltage, temperature);
 
  Serial.print("Temperature:");
  Serial.print(temperature, 2);
  Serial.println("ºC");
 
  Serial.print("EC:");
  Serial.println(ecValue, 2);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Water Quality"));
  display.println(F("Monitoring System"));

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
 
  display.setCursor(0, 20);
  display.print("T:");
  display.print(temperature, 2);
  display.drawCircle(90, 20, 2, SSD1306_WHITE);
  display.setCursor(95, 20);
  display.print("C");
 
  display.setCursor(0, 50);
  display.print("EC:");
  display.print(ecValue, 2);

  display.display();

  delay(1500);
  display.clearDisplay();
 
  ec.calibration(voltage, temperature);
 
  if (client.connect(server, 80))
  {
 
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temperature, 2);
    postStr += "&field2=";
    postStr += String(ecValue, 2);
    postStr += "\r\n\r\n";
    delay(500);
 
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    delay(500);
  }
  client.stop();
}