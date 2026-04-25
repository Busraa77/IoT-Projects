#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6nssBPzJJ"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "zEzlR_chyZcGD_l_-917mEGsfM_BoORP"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "FiberHGW_TP2B22_2.4GHz";
char pass[] = "zTudjnXz";

#define RED D4
#define GREEN D5
#define BLUE D6

BLYNK_WRITE(V4)
{
int r = param.asInt();
analogWrite(RED, r);
}

BLYNK_WRITE(V5)
{
int g = param.asInt();
analogWrite(GREEN, g);
}

BLYNK_WRITE(V6)
{
int b = param.asInt();
analogWrite(BLUE, b);
}

void setup()
{
Serial.begin(9600);

pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);

analogWriteRange(255);

Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

 WiFi.begin(ssid, pass);

  int wifiTry = 0;
  while (WiFi.status() != WL_CONNECTED && wifiTry < 40) {
    delay(500);
    Serial.print(".");
    wifiTry++;
  }
}

void loop()
{
Blynk.run();
}