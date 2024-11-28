#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Cấu hình WiFi
const char* ssid = "hqc";
const char* password = "haquoccuong";

// Địa chỉ server (thay bằng IP của máy tính của bạn)
const char* serverName = "http://192.168.230.21:5000/update_light/";

BH1750 lightMeter;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    lightMeter.begin();

     WiFi.begin(ssid, password);
    Serial.print("Đang kết nối WiFi");
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nĐã kết nối WiFi!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nKhông thể kết nối WiFi!");
        while(1);
    }
}

void loop() {
    if(WiFi.status() == WL_CONNECTED) {
        float lux = lightMeter.readLightLevel();
        
        // Tạo URL với giá trị đo được
        String url = String(serverName) + String(lux);
        
        HTTPClient http;
        http.begin(url);
        
        // Gửi GET request
        int httpResponseCode = http.GET();
        
        if (httpResponseCode > 0) {
            Serial.print("Light: ");
            Serial.print(lux);
            Serial.println(" lx");
        } else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        
        http.end();
    }
    
    delay(1000);  // Đọc và gửi dữ liệu mỗi giây
}