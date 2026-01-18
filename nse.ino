// NeuralSense Environmental Intelligence System - FIXED VERSION

#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"
#include "MQ135.h"

// --- 1. CONFIGURATION ---
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

unsigned long CHANNEL_ID = YOUR_THINKSPEAK_CHANNEL_ID;
// ACTION: CHECK THIS KEY! It must be 16 characters. Yours was 15.
const char* WRITE_API_KEY = "YOUR_THINKSPEAK_WRITE_API_KEY"; 

#define DHT_PIN 4      // D2 (GPIO4)
#define MQ135_PIN A0   // Analog Pin

#define DHT_TYPE DHT11

// --- 2. SENSOR OBJECTS ---
WiFiClient client;
DHT dht(DHT_PIN, DHT_TYPE);
MQ135 gasSensor = MQ135(MQ135_PIN);

// Timing variables
const long UPLOAD_INTERVAL = 30000; 
unsigned long lastUploadTime = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  Serial.println("\n\n[System] Starting NeuralSense...");
  
  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[Success] WiFi Connected. IP: " + WiFi.localIP().toString());

  // --- MQ135 CALIBRATION HELP ---
  // The sensor needs to 'burn in' (heat up) for at least 60 seconds before reliable reading
  Serial.println("[Sensor] Warming up MQ135 (Please wait 20s)...");
  delay(20000); 
  
  // This prints the RZero value you need to copy-paste into your library file or code
  float rzero = gasSensor.getRZero();
  Serial.print("[CALIBRATION] Your Current RZero is: ");
  Serial.println(rzero);
  Serial.println("[CALIBRATION] If this value is very different from 76.63, update your code or library.");
}

void loop() {
  // Check if 30 seconds have passed
  if (millis() - lastUploadTime > UPLOAD_INTERVAL) {
    
    // 1. Check WiFi Connection
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[Error] WiFi lost. Reconnecting...");
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      return; 
    }

    // 2. Read Sensors
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    // Calculate PPM
    // Note: If you didn't edit the library file with the RZero found in setup, this will still be offset.
    float ppm = gasSensor.getCorrectedPPM(t, h);

    if (isnan(h) || isnan(t)) {
      Serial.println("[Error] Failed to read from DHT sensor!");
      return;
    }

    // 3. Debug Print
    Serial.println("\n--------------------");
    Serial.print("Temp: "); Serial.print(t); Serial.println(" C");
    Serial.print("Hum:  "); Serial.print(h); Serial.println(" %");
    Serial.print("CO2:  "); Serial.print(ppm); Serial.println(" PPM");
    Serial.println("--------------------");

    // 4. Upload to ThingSpeak
    ThingSpeak.setField(1, t);
    ThingSpeak.setField(2, h);
    ThingSpeak.setField(3, ppm);

    int httpCode = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);

    if (httpCode == 200) {
      Serial.println("[Success] ThingSpeak update successful.");
    } else {
      Serial.print("[Error] ThingSpeak Update Failed. HTTP Error Code: ");
      Serial.println(httpCode);
      
      // Error Code Explanations
      if (httpCode == 401) Serial.println(" -> REASON: Wrong API Key (Check spelling/length)");
      if (httpCode == -301) Serial.println(" -> REASON: Connection Failed");
      if (httpCode == -304) Serial.println(" -> REASON: Timeout");
      if (httpCode == 0) Serial.println(" -> REASON: Generic Error (Check WiFi/Library)");
    }
    
    lastUploadTime = millis();
  }
}
