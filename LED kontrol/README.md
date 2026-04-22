# LED KONTROLÜ (NODE MCU ve GOOGLE FİREBASE)

Bu projede ESP8266 tabanlı NodeMCU kullanılarak Firebase Realtime Database üzerinden internet aracılığıyla LED kontrolü yapılmıştır.

## Proje Amacı

Firebase veritabanındaki bir değeri okuyarak NodeMCU üzerindeki LED’i uzaktan açıp kapatmak.

### Kullanılan Teknolojiler
NodeMCU (ESP8266)  
Arduino IDE  
Firebase Realtime Database  
Wi-Fi bağlantısı  
Firebase ESP8266 Client kütüphanesi  


### Sistem Mantığı  

Firebase içerisinde bulunan LED_DURUM değeri NodeMCU tarafından sürekli okunur.

"YAK" → LED yanar  
"SONDUR" → LED söner  


### Devre Bağlantısı
LED uzun bacak → D3 pini  
LED kısa bacak → 330Ω direnç → GND  

### Firebase
Bir proje oluşturun. Projeniz içine key:value olarak  LED_DURUM: SONDUR veya YAK şeklinde tanımlama yapın.  Her değer değiştirdiğinizde LED ona göre değişecek.

### Kod Düzenlemesi
const char* ssid = ""; için Wi-Fi ağınızın ismini yazınız. Node MCU kartı 2.4 GHz ağları görebilir, 5 GHz ağları göremez ya da bağlanamaz.    

const char* password = ""; için Wi-Fi şifrenizi yazın.   

#define FIREBASE_HOST "" için Firebase'deki projenizin Realtime Database'inde bulan URL'i başında http:// ve sonunda / olmadan yazın.  

#define FIREBASE_AUTH "" için Firebase'de Settings -> Service Accounts -> Database Secrets'daki şifrenizi boşluksuz olarak yapıştırın.  


### Kod
```
#include <ESP8266WiFi.h> //Wi-Fi işlemleri- kartın internete bağlanmasını sağlayan araçları getiriyor.
#include <FirebaseESP8266.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

FirebaseData fbdo; //firebaseden gelen veriyi tutar.
FirebaseAuth auth; //Kimlik doğrulama bilgilerini tutar.
FirebaseConfig config; //Firebase ayarlarını tutar. host token bilgileri tutar.

const char* ssid = "";
const char* password = "";

byte led=D3;
void setup() {
  pinMode(led, OUTPUT);
  
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("NodeMCU basliyor...");
  Serial.print("Baglanilan WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); //Bağlantı denemesini başlatır.

  while (WiFi.status() != WL_CONNECTED) { //bağlanana kadar bekle 
    delay(500);
    Serial.print("."); //bağlanmaya çalıştığını gösterir.
  }

  Serial.println();
  Serial.println("WiFi baglandi.");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.localIP()); //Bağlandıktan sonra kartın ağdaki adresini gösterir.

  config.host = FIREBASE_HOST;
config.signer.tokens.legacy_token = FIREBASE_AUTH;

Firebase.begin(&config, &auth);
/*bu fonksiyon şöyle tanımlanmış: begin(FirebaseConfig *config, FirebaseAuth *auth)
pointer bekliyor*/
Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.getString(fbdo, "/LED_DURUM")) { // Firebase verileri yol mantığıyla tutulur.

  String fireStatus = fbdo.stringData();

  if (fireStatus == "YAK") {
  digitalWrite(led, HIGH);
}
else if (fireStatus == "SONDUR") {
  digitalWrite(led, LOW);
}
else {
  Serial.println("Firebase okuma hatasi");
  Serial.println(fbdo.errorReason());
}
}

delay(1000);}

```
