#include "wifi_handler.h"
#include <WiFi.h>

// Nazwa sieci WiFi i hasło
const char *ssid = "Hotto-Spotto";
const char *password = "01234567890";

// Funkcja inicjalizująca połączenie WiFi
void setupWiFi()
{
    Serial.print("[WiFi] 🔄 Łączenie z siecią: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20)
    {
        delay(500);
        Serial.print(".");
        retries++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\n[WiFi] ✅ Połączono!");
        Serial.print("[WiFi] 📡 Adres IP: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("\n[WiFi] ❌ Nie udało się połączyć!");
    }
}
