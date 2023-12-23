/*
  Youtube  : https://www.youtube.com/c/403ERRORVN
  Fanpage  : https://www.facebook.com/403ERRORVN
  Blog     : https://thichchetaotv.blogspot.com/

  Date     : 25/05/2022
  Update   : 

  Library
* Lora E32: https://github.com/xreef/LoRa_E32_Series_Library
* TFT_eSPI :https://github.com/Bodmer/TFT_eSPI

*/

TaskHandle_t Task2;

#include "iconSuDung1.h"
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#include "LoRa_E32.h"
LoRa_E32 e32ttl(&Serial2); //  RX AUX M0 M1 (ESP32)

//===== Blynk IOT =====//
#define BLYNK_TEMPLATE_ID "TMPL6YzGvQiqb"
#define BLYNK_TEMPLATE_NAME "Thoi Tiet"
#define BLYNK_AUTH_TOKEN "4IH5_-swXIP4gL8348HuN4qXTIoCbvrW"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Giao Dzai";
char pass[] = "17072003";
TaskHandle_t Core2;
BlynkTimer timer;
WidgetRTC rtc;


BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
}


#define ledRun   21
#define ledAlarm 5
#define buzz     12


// -------------------------------------
void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);

long dv, chuc, tram, nghin, chucnghin;
int s;
long t1, t2, t3, t4, t5;
String str = "";
String currentTime, currentDate;

float
nhietdo1,
doam1   ,
bui1    ,
mua1    ,
nhietdo2,
doam2   ,
bui2    ,
mua2    ,
buiHigh = 150.00,
batLow  = 3.60;

unsigned long
previousMillis        = 0,
currentMillis         = 0,
prevSerialMillis      = 0,
currentSerialMillis   = 0,
prevBlynkMillis      = 0,
currentBlynkMillis = 0;

int
ledState   = 0,
mauCanhBao = 0,
ERR        = 0,
ERR2       = 0;

void clockDisplay()
{
  currentTime = String(hour()) + ":" + minute() + ":" + second();
  currentDate = String(day()) + " " + month() + " " + year();
}

void setup()
{
  Serial.begin(115200);

  pinMode(ledRun, OUTPUT);
  pinMode(ledAlarm, OUTPUT);
  pinMode(buzz, OUTPUT);

  digitalWrite(ledRun, HIGH);
  digitalWrite(ledAlarm, HIGH);

  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  e32ttl.begin();

  // ---------------------------


  xTaskCreatePinnedToCore(
    Task2code,   /* Task function. */
    "Task2",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task2,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */

} // end Setup

void Task2code( void * pvParameters ) {
  Blynk.begin(auth, ssid, pass);
  setSyncInterval(5); // Sync interval in seconds (10 minutes)
  while (1) {
    senBlynk();
    Blynk.run();
    timer.run();
  }
}

void loop()
{
  NhanDuLieu();
  TFT_Print();
  Onboard_Telemetry();
  
} // end loop
