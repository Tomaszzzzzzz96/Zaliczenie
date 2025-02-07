#include <FS.h>
#include <SPIFFS.h>
#include <Arduino_JSON.h>
#include "json_handler.h"
#include "server_handler.h"

// Funkcja zapisująca PIN do pliku JSON
void savePinToJson(const String &pin)
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("[SPIFFS] ❌ Błąd inicjalizacji!");
        return;
    }

    JSONVar pinData;
    pinData["pin"] = pin;

    File file = SPIFFS.open("/pin_data.json", "w");
    if (!file)
    {
        Serial.println("[JSON] ❌ Błąd zapisu pliku!");
        return;
    }

    file.print(JSON.stringify(pinData));
    file.close();
    Serial.println("[JSON] ✅ PIN zapisany w pliku!");

    //    sendJsonToServer(); // Wysyłanie pliku do serwera
}

// Funkcja odczytująca PIN z pliku JSON
String readPinFromJson()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("[SPIFFS] ❌ Błąd inicjalizacji!");
        return "";
    }

    if (!SPIFFS.exists("/pin_data.json"))
    {
        Serial.println("[SPIFFS] ⚠️ Brak pliku PIN! Tworzę nowy...");
        savePinToJson("1234");
        return "1234";
    }

    File file = SPIFFS.open("/pin_data.json", "r");
    if (!file)
    {
        Serial.println("[JSON] ❌ Błąd otwarcia pliku!");
        return "";
    }

    String content = file.readString();
    file.close();

    JSONVar jsonData = JSON.parse(content);
    if (JSON.typeof(jsonData) == "undefined")
    {
        Serial.println("[JSON] ❌ Błąd parsowania JSON! Resetowanie...");
        savePinToJson("1234");
        return "1234";
    }

    return jsonData.hasOwnProperty("pin") ? (const char *)jsonData["pin"] : "";
}
