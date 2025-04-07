# AlertBot
Alert Bot System with ESP32

# English

## **ESP32-Based Telegram-Controlled Alarm System **

---

### **Introduction – A Brother’s Revenge (!)**

This project was born from a very *personal and slightly vengeful* motivation. My sister has this talent for sleeping through *everything*—especially when she sets her phone to silent mode. No call, no notification, no chance.

So, I thought: “If she won’t hear her phone, why don’t *I* make the house ring remotely?” That’s how I ended up creating a system where I can trigger a loud home alarm from anywhere in the world using a **Telegram bot and an ESP32**.

---

### **Project Overview**

This project allows a traditional 15V AC bell to be activated remotely using an **ESP32 microcontroller** and a **Fotek SSR (Solid State Relay)**. The whole system is controlled via **Telegram**, meaning you can make it ring from your phone—no matter where you are.

---

### **Components Used**

- **ESP32 Development Board**  
- **Fotek SSR-10 DA (Solid State Relay)**  
- **15V AC Transformer (220V input, 15V output)**  
- **Wiring and connection hardware**  
- **15V AC Mechanical Bell**

---

### **System Architecture**

1. **Telegram Bot**  
   A bot built using the UniversalTelegramBot library receives and processes your commands.

2. **ESP32**  
   Connects to Wi-Fi and listens for bot messages. It then controls the SSR output accordingly.

3. **SSR Relay**  
   Switches the 220V AC line that feeds into the transformer, based on the ESP32’s GPIO signal.

4. **Transformer + Bell**  
   The transformer converts 220V to 15V AC to ring the bell when SSR is activated.

---

### **Working Principle**

1. The user sends the `/alarm_on` command to the Telegram bot.  
2. ESP32 processes the command and turns the SSR on.  
3. 220V reaches the transformer → 15V AC output → the bell rings.  
4. The `/alarm_off` command turns everything off.  
5. `/state` checks and reports the current status of the alarm system.

---

### **Code Summary**

The code handles Wi-Fi connection and Telegram messaging. The `handleNewMessages()` function checks for incoming commands and toggles the GPIO pin to control the bell.

**Telegram Commands:**

- `/start` → Greets you and shows available commands.  
- `/alarm_on` → Rings the bell.  
- `/alarm_off` → Stops the bell.  
- `/state` → Tells you whether the bell is currently active.

---

### **Safety Notes**

- The SSR handles high-voltage AC; connections must be secure and insulated.  
- Only the user with the correct Telegram Chat ID can control the device.  
- The transformer and bell setup should be handled carefully to avoid shock or short circuits.

---

### **Conclusion**

This system is the perfect remote sibling-wakeup solution. If your sister's phone is on silent, don’t stress—just ring the whole house instead. Thanks to the **ESP32 + Telegram combo**, you can now *wake her up from across the globe*.


# Türkçe
---

## **ESP32 Tabanlı Telegram Kontrollü Alarm Sistemi

---

### **Giriş – Bir Kardeşin Çığlığı (!)**

Bu proje, tamamen **kişisel ve kardeşsel** bir motivasyonla ortaya çıktı. Evde olmadığım zamanlarda, kardeşimi önemli bir iş için uyandırmam gerektiğinde sıkıntı yaşıyordum. Çünkü kendisi, tam bir “telefon sessize alıcı” uzmanı. Ne aramalar ne mesajlar, hiçbir şey yankılanmıyor. Ama evdeki klasik zil sesi… İşte o kaçmaz!

Bu noktada aklıma geldi: “Madem ki o telefonu duymuyor, o zaman **ben neden evi uzaktan çaldırmayayım?**” dedim ve bir Telegram botuyla ESP32 üzerinden kontrol edilen bir alarm sistemi yapmaya karar verdim.

---

### **Sistem Hakkında Genel Bilgi**

Bu proje, **ESP32** mikrodenetleyicisi ve **Fotek SSR (Solid State Relay)** kullanılarak 15V AC ile çalışan klasik bir zilin, uzaktan **Telegram üzerinden tetiklenmesini** sağlar. Yani siz dünyanın herhangi bir yerinden, Telegram üzerinden belirli komutlarla evdeki zili çaldırabilirsiniz.

---

### **Kullanılan Malzemeler**

- **ESP32 Devre Kartı**
- **Fotek SSR-10 DA** (Solid State Röle)
- **15V AC Trafo (220V giriş, 15V çıkış)**
- **Kablolar ve bağlantı ekipmanları**
- **Zil (15V AC ile çalışan klasik mekanik zil)**

---

### **Sistem Mimarisi**

1. **Telegram Bot:**  
   UniversalTelegramBot kütüphanesi kullanılarak, ESP32 ile bir Telegram botu üzerinden haberleşme sağlanır.

2. **ESP32:**  
   WiFi ağına bağlanır ve gelen Telegram mesajlarını dinler. Belirli komutlar geldiğinde röleyi tetikler.

3. **SSR Röle:**  
   ESP32 üzerinden gelen dijital sinyalle çalışır. Bu röle, ESP32’nin çıkışındaki 3.3V ile aktif hale gelerek 220V tarafındaki AC devresini açar ve trafoya 220V gönderilmesini sağlar.

4. **Trafo + Zil:**  
   Röle üzerinden gelen 220V, trafoya ulaştığında 15V AC üretir ve bu da zile gönderilerek zilin çalmasını sağlar.

---

### **Çalışma Prensibi**

1. Kullanıcı, Telegram botuna **/alarm_on** komutu gönderir.
2. ESP32, bu komutu aldığında röleyi aktif eder.
3. Röle üzerinden geçen 220V, trafoya ulaşır.
4. Trafo, 15V AC çıkış üretir ve zil çalar.
5. Komutlar arasında **/alarm_off** ile sistem pasif hale getirilir.
6. Kullanıcı ayrıca **/state** komutuyla sistemin aktif/pasif durumunu öğrenebilir.

---

### **Kod Özeti**

Kod, ESP32'nin Telegram bot ile haberleşmesini sağlarken aynı zamanda GPIO pinine bağlı SSR’yi kontrol eder. Telegram üzerinden gelen mesajlar `handleNewMessages()` fonksiyonu ile işlenir.

Örnek komutlar:

- `/start` → Kullanıcıyı karşılar, komutları listeler.
- `/alarm_on` → Röleyi açar, zil çalar.
- `/alarm_off` → Röleyi kapatır.
- `/state` → Zil sisteminin durumunu bildirir.

---

### **Güvenlik Notları**

- SSR kullanılırken dikkatli olunmalıdır, çünkü 220V AC hattıyla çalışmaktadır.
- Trafo bağlantıları izole edilerek yapılmalıdır.
- Telegram Bot sadece belirli bir kullanıcı ID’sine izin verir, böylece dış müdahale engellenmiş olur.

---

### **Sonuç**

Bu proje, eğlenceli ama bir o kadar da pratik bir çözüm sundu. Kardeşinizi uzaktan kaldırmak mı istiyorsunuz? Telefonu sessize mi aldı? Hiç sorun değil. Artık **"uzaktan zil"** devrede! Bu sistem sayesinde Telegram üzerinden dünyanın neresinde olursanız olun, evdeki zili çaldırabilir ve görevlerinizi yerine getirebilirsiniz.

