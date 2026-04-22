

https://github.com/user-attachments/assets/12064fd4-33e9-4f32-a5d7-695fe426260f

# WEB SAYFASINDAN LED KONTROLÜ (NODEMCU + HTML)

Bu projede ESP8266 tabanlı NodeMCU kullanılarak basit bir web sunucusu oluşturulmuş ve internet tarayıcısı üzerinden LED kontrolü gerçekleştirilmiştir.

### Proje Amacı

NodeMCU üzerinde çalışan web sayfası aracılığıyla LED’i açıp kapatmak. Kullanıcı, NodeMCU’nun IP adresine tarayıcıdan bağlanarak oluşturulan HTML sayfası üzerinden LED kontrolü yapabilir.  


### Kullanılan Teknolojiler

- NodeMCU (ESP8266)  
- Arduino IDE  
- HTML  
- Wi-Fi bağlantısı  
- ESP8266WiFi kütüphanesi  

### 
Arduino IDE içerisine ESP8266WiFi.h kütüphanesi eklenmelidir.  
Daha detaylı anlatım için LED kontrol proojesini inceleyebilirsiniz.  
client, bağlanan tarayıcıyla aradaki iletişim nesnesidir. 

```
#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";

int led = D3;                 
WiFiServer server(80);        // 80 portunda web sunucusu

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);     // başlangıçta LED sönük

  Serial.println();
  Serial.println("Baglaniyor...");

  Serial.print("SSID: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // Wi-Fi bağlantısı başlat

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi baglantisi saglandi.");
  Serial.println("Web sunucu basladi.");

  server.begin();

  Serial.print("Web sunucuya baglanmak icin bu baglantiyi kullanin: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();   // İstemci bağlandı mı?
  if (!client) { //bağlı kimse yoksa dur
    return;
  }

  Serial.println("Yeni istemci");

  while (!client.available()) { //İstemciden gelen okunmaya hazır bir veri var mı?
    delay(1);
  }

  String request = client.readStringUntil('\r'); // Gelen isteği oku
  Serial.println(request);
  client.flush();

  int deger = LOW;   // LED durumu

  if (request.indexOf("/LEDYAK") != -1) { //gelen veri içinde bu metin varsa bir sayı döndürür yoksa -1
    digitalWrite(led, HIGH);
    deger = HIGH;
  }

  if (request.indexOf("/LEDSONDUR") != -1) {
    digitalWrite(led, LOW);
    deger = LOW;
  }

  // HTML sayfasını gönder
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");  // boş satır

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset='UTF-8'>");
  client.println("<title>NodeMCU LED Uygulamasi</title>");
  client.println("<style>");
  client.println("body { background-color: yellow; text-align: center; font-family: Arial; }");
  client.println("button { padding: 10px 20px; font-size: 16px; margin: 8px; }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");

  client.println("<h2>Node MCU LED uygulamasi</h2>");
  client.print("LED DURUM: ");

  if (deger == HIGH) {
    client.println("<b>Yaniyor</b><br><br>");
  } else {
    client.println("<b>Sonuk</b><br><br>");
  }

  client.println("<a href=\"/LEDYAK\"><button>Ledi yak</button></a>");
  client.println("<a href=\"/LEDSONDUR\"><button>Ledi sondur</button></a>");

  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Istemci baglantisi kapandi.");
}
```
