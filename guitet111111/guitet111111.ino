

/*
  Youtube  : https://www.youtube.com/c/403ERRORVN
  Fanpage  : https://www.facebook.com/403ERRORVN
  Blog     : https://thichchetaotv.blogspot.com/

  Date     : 25/05/2022
  Update   :

  Library
  Lora E32: https://github.com/xreef/LoRa_E32_Series_Library
  DHT     : https://github.com/adafruit/DHT-sensor-library

*/

#include "LoRa_E32.h"
LoRa_E32 e32ttl(8, 9);

#include "DHT.h"
#define DHTPIN 5  // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define tbi 1       //  Bộ phát số 1
int cambien = 4;
int
volPin = A1,
tt,
hh,
mua;

float
h,
t,
vout = 0,
vin  = 0,
R1 = 30000.0,
R2 = 7200.0;

int dustPin = A0;
int ledPower = 10;

int dustVal = 0;
char s[32];
float
dustdensity = 0.0000,
dustRaw     = 0.0000,
voltage     = 0.0000;

int avgDust = 10;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPower, OUTPUT);
  dht.begin();
  Serial. begin (9600);
  pinMode (cambien, INPUT);
  e32ttl.begin();
}

// The loop function is called in an endless loop
void loop()
{
  h = dht.readHumidity();
  t = dht.readTemperature();

  vin = analogRead(volPin) * (5.0 / 1023.0); // see text
  hh  = h * 10;
  tt  = t * 10;
  int digital = digitalRead(cambien);
  cambienbui();
  int bui =  dustdensity * 10.0;
 
 

  Serial.print("Temp : ");  Serial.print(t);
  Serial.print(" Hum  : "); Serial.print(h);
  Serial.print(" PM2.5: "); Serial.print(dustdensity);
  Serial.print(" mua: "); Serial. println(digital);
 
  
  if (runEvery(5000)) {
    String mess1 = 'a' + String(tbi) + 'b' + String(tt) + 'c' + String(hh) + 'd' + String(bui) + 'e' + String(mua) + 'f'  ;
    //Serial.println(mess1);
    ResponseStatus rs = e32ttl.sendFixedMessage(0, 6, 0x09, mess1);
  }
  
}

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

void cambienbui()
{
  // if (runEvery(1000)) {
  digitalWrite(ledPower, LOW); // power on the LED
  delayMicroseconds(280);
  dustVal = analogRead(dustPin); // read the dust value
  delayMicroseconds(40);
  digitalWrite(ledPower, HIGH); // turn the LED off
  delayMicroseconds(9680);

  voltage = (dustVal * 5 / 1024.0); //dustval*5/1024

  dustRaw = 0.0000;
  for (int i = 0; i < avgDust; i++) {
    //dustRaw = dustRaw + 57*voltage;
    dustRaw = dustRaw + 0.17 * voltage - 0.1;
  }
  dustdensity = (dustRaw / avgDust) * 1000.0; // ug/m3

  if (dustdensity < 0 )
    dustdensity = 0;
  if (dustdensity > 500)
    dustdensity = 500;
  //}
}
