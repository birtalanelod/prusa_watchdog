/*
Prusa Watchdog by Birtalan Előd 2019

Ver.   Date          Information
V1.0   2019.10.31    Initial Release  

This code is in the public domain.


*/
//#define DEBUG 0


#include "arduino_secrets.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>
#include <Adafruit_NeoPixel.h>
#include <Chrono.h> 



// Initialize Wifi connection to the router
const char* ssid  = SECRET_SSID;
const char* password = SECRET_PASS;

// Initialize Telegram BOT
const char* chat_id=SECRET_CHAT_ID;
const char BotToken[] = SECRET_BOT_TOKEN;


//---------------------------------Connections---------------------------------------
const int smokeSens_PIN = A0; // dust sensor - Wemos D1 Mini A0 pin
const int smokeLed_PIN = D2; 
const int pixel_PIN = D1;   
const int relay_PIN = D3;
//const int button_PIN = D4;
//-----------------------------------------------------------------------------------
bool offline=false;   // Set this true for OFFLINE MODE 
bool disconected=false;

int smokeVal=0; 
int maxSmoke=0;
const int smokeLimit=500;    // Change this value to  ALARM THRESHOLD 

bool blink_Flag=false;
bool alarm=false;


byte RGB[7][3] = {
  //  R,  G,  B
  {  0,   0,   0},         //  0 BLACK _LED OFF, used for blinking LED every  cycle to show the program is running
  {  255, 0,   0},         //  1 RED   -ALARM ON SMOKE DETECTED
  {0,   25,   25},         //  2 CIAN  -OK_ONLINE   
  {0,   50,  0},           //  3 GREEN -OK_OFFLINE MOD    
  {255, 255, 255},         //  4 WHITE -SENDING MESSAGE TO TELEGRAM 
  {0, 0, 255} ,            //  5 BLUE  -not used
  {25, 25, 0}              //  6 YELLOW -DISCONECTED 
};
byte R=0;
byte G=0;
byte B=0;
byte color=2;

WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, pixel_PIN, NEO_GRB + NEO_KHZ800);
Chrono timer(Chrono::SECONDS);



void setup() {

  strip.begin();

  pinMode(smokeLed_PIN,OUTPUT);
  pinMode(relay_PIN,OUTPUT);
  digitalWrite(relay_PIN, HIGH); 
 
 Serial.begin(115200);
 Serial.println(F(" "));
 Serial.println(F("Prusa WatchDog 2019"));
 Serial.print(F("VER: "));
 Serial.println(F(__DATE__));
 Serial.print(F("BUILD: "));
 Serial.println(F(__TIME__));

 

go_online(); // connects(BLUE) online(CIAN) or starts deivce in offline mode (GREEN),function in wifi tab
 

}

void loop() {
  
check_wifi();      // check if connected to wifi , if is disconected-yellow
check_smoke();     // measure smoke, triger alarm & actions
blink_led();       // blinking STATUS LED 
status_update(60); // send every X second Power Status( |=ON, O=OFF)and SMV (Smoke Value to Telegram) 

}
