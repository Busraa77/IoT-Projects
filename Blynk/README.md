# BLYNK ile RGB LED Renk Yönetimi

Blynk IoT projelerinde kullanılan donanımımıza uzaktan erişim sağlayan, veri depolayabilen bir uygulamadır. Bu projenin amacı uygulamayı kullanarak RGB LED'imiz üzerinde renk değişiklikleri yapmaktır.  

### Donanım Kurulumu
RGB LED'imizi normal şekilde NodeMCU'muza bağlayacağız. Burada RGB LED'in anot veya katot olmasına göre bağlantı şeklimiz değişiyor. Katot ise uzun bacağını - yani GND'ye anot ise + yani 3V'ye bağlayacağız.  
Katot olması durumunda okuduğumuz değerleri 255 den çıkarmamız gerekiyor ancak anot ise değerleri direkt kullanırız. Bu projede ortak anot RGB LED kullanılmıştır.
Bu projede bağlantı için D4,D5 ve  D6 pinleri kullanılmıştır. Ancak NodeMCU'da D0 hariç tüm pinlerin PWM desteği olduğu için istediğiniz pini seçebilirsiniz.

### Blynk Template Oluşturma
Blynk'i telefonunuza indirerek red,green ve blue için 3 farklı slider kullanmalısınız. 

<img width="540" height="1018" alt="blynkpic" src="https://github.com/user-attachments/assets/3b847a82-454b-4f07-8a3b-9b9349eaf741" />

### Kod
```
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "";
char pass[] = "";

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
```
