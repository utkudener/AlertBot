#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

// Wi-Fi bağlantısı için ağ bilgileri
const char* ssid = "*****";  // Wi-Fi SSID
const char* password = "*********";   // Wi-Fi şifresi

// Telegram botu için gerekli Token ve Chat ID
#define BOTtoken "*******************"  // Bot Token (Botfather'dan alınır)
#define CHAT_ID "************"  // Chat ID (Bireysel veya grup chat ID'si)

WiFiClientSecure client;  // Güvenli Wi-Fi istemcisi
UniversalTelegramBot bot(BOTtoken, client);  // Telegram botu

// Bot'un mesajları kontrol etme aralığı (1 saniye)
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;  // Bot'un son çalıştırma zamanı

// Alarm kontrolü için kullanılan pin (Alarmı kontrol eden pin)
const int alarmPin = 16;  
bool alarmState = LOW;  // Alarm başlangıçta kapalı (LOW)


// Telegram'dan gelen yeni mesajları işleyen fonksiyon
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Gönderen chat id'si
    String chat_id = String(bot.messages[i].chat_id);
    
    // Yetkisiz kullanıcılar için mesaj gönder
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Alınan mesajı yazdır
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    // Kullanıcı /start komutunu gönderdiğinde
    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control the alarm system.\n\n";
      welcome += "/alarm_on to turn the alarm ON \n";
      welcome += "/alarm_off to turn the alarm OFF \n";
      welcome += "/state to request current alarm state \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    // Alarmı açma komutu
    if (text == "/alarm_on") {
      bot.sendMessage(chat_id, "Alarm state set to ON", "");
      alarmState = HIGH;  // Alarmı aç
      digitalWrite(alarmPin, alarmState);  // Alarm pinini HIGH yap
    }
    
    // Alarmı kapama komutu
    if (text == "/alarm_off") {
      bot.sendMessage(chat_id, "Alarm state set to OFF", "");
      alarmState = LOW;  // Alarmı kapat
      digitalWrite(alarmPin, alarmState);  // Alarm pinini LOW yap
    }
    
    // Alarmın mevcut durumunu sorgulama komutu
    if (text == "/state") {
      if (digitalRead(alarmPin)){
        bot.sendMessage(chat_id, "Alarm is ON", "");
      }
      else{
        bot.sendMessage(chat_id, "Alarm is OFF", "");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);  // Seri monitör başlatılıyor

  pinMode(alarmPin, OUTPUT);  // Alarm pinini çıkış olarak ayarla
  digitalWrite(alarmPin, alarmState);  // Alarm başlangıçta kapalı

  // Wi-Fi'ye bağlan
  WiFi.mode(WIFI_STA);  // Wi-Fi durumunu STA (Client) olarak ayarla
  WiFi.begin(ssid, password);  // Wi-Fi bağlantısını başlat

  // Wi-Fi bağlantısı sağlanana kadar bekle
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Bağlantı sağlandığında IP adresini yazdır
  Serial.println(WiFi.localIP());

  // Telegram API için gerekli sertifikayı ayarla
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Telegram için root sertifikası
}

void loop() {
  // Bot'un her saniyede bir yeni mesajları kontrol etmesini sağlar
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    // Yeni mesajları al
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    // Mesajları işle
    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    // Son işlem zamanı güncelleniyor
    lastTimeBotRan = millis();
  }
}
