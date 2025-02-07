#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Hotto-Spotto";
const char* password = "01234567890";
const char* serverUrl = "http://192.168.159.40:8080/sensor"; // Replace with your Go server's IP address

const int pirPin = 13;
bool isArmed = true;
bool motionDetected = false;
int sensitivity = 50; // Default sensitivity (0-100)
unsigned long lastTestTime = 0;
const unsigned long TEST_INTERVAL = 120000; // 2 minutes in milliseconds

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check for motion
  if (isArmed) {
    bool currentMotion = digitalRead(pirPin) == HIGH;
    if (currentMotion != motionDetected) {
      motionDetected = currentMotion;
      sendSensorData();
      if (motionDetected) {
        Serial.println("Motion detected!");
      }
    }
  }

  // Test every 2 minutes
  if (millis() - lastTestTime >= TEST_INTERVAL) {
    performTest();
    lastTestTime = millis();
  }

  delay(100);
}

void performTest() {
  bool testResult = digitalRead(pirPin) == HIGH;
  Serial.println("Sensor test: " + String(testResult ? "Motion detected" : "No motion"));
  // You can also send this test result to the server if needed
}

void sendSensorData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(200);
    doc["armed"] = isArmed;
    doc["motion"] = motionDetected;
    doc["sensitivity"] = sensitivity;

    String json;
    serializeJson(doc, json);

    int httpResponseCode = http.POST(json);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Server response: " + response);
    } else {
      Serial.println("Error sending POST: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}
