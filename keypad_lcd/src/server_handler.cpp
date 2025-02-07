#include "server_handler.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <SPIFFS.h>

// Adres lokalnego serwera
const char *serverURL = "http://192.168.159.40:8080/validate/pin";

// Funkcja testująca połączenie z serwerem
void testServerConnection()
{
    HTTPClient http;
    http.begin("http://10.3.213.142:5000/"); // Sprawdzenie dostępności serwera
    int httpResponseCode = http.GET();

    if (httpResponseCode = 200)
    {
        Serial.printf("[TEST] ✅ Odpowiedź serwera: %d\n", httpResponseCode);
    }
    else
    {
        Serial.printf("[TEST] ❌ Błąd połączenia! Kod: %d\n", httpResponseCode);
    }

    http.end();
}

// Funkcja wysyłająca dane JSON do serwera
bool sendJsonToServer(String pin)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("[WiFi] ❌ Brak połączenia z siecią!");
        return false;
    }

    // testServerConnection(); // Dodanie testowego żądania GET
    JSONVar pinData;
    pinData["pin"] = pin;
    String jsonData = JSON.stringify(pinData);

    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);

    http.end();

    if (httpResponseCode == 200)
    {
        Serial.printf("[SERVER] ✅ Odpowiedź serwera: %d\n", httpResponseCode);
        return true;
    }
    else
    {
        Serial.printf("[SERVER] ❌ Błąd wysyłania danych! Kod: %d\n", httpResponseCode);
        return false;
    }
}
