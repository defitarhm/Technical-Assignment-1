#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Konfigurasi pin dan WiFi
const char* ssid = "FIK-Hotspot";  // Ganti dengan SSID WiFi Anda
const char* password = "FIK22-23!";  // Ganti dengan password WiFi Anda
const char* serverName = "http://172.23.22.75:8000/create";  // Ganti dengan alamat server Anda
#define MQPIN 34 // Pin analog untuk sensor MQ

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int mqValue = analogRead(MQPIN); // Membaca nilai sensor MQ

    // Create JSON object
    StaticJsonDocument<200> doc;
    doc["name"] = "ESP32";
    doc["value"] = mqValue;

    String requestBody;
    serializeJson(doc, requestBody);

    Serial.println(mqValue);
    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(2000);  // Tunggu 60 detik sebelum mengirim data lagi
}
