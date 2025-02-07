#include "lcd_display.h"
#include "keypad_handler.h"
#include "json_handler.h"
#include "wifi_handler.h"
#include "server_handler.h"
#include <SPIFFS.h>
#include <Arduino.h>

void setup()
{
    Serial.begin(115200); // Inicjalizacja komunikacji szeregowej
    Serial.println("🚀 System startup...");

    setupWiFi(); // Połącz z Wi-Fi

    if (!SPIFFS.begin(true))
    {
        Serial.println("[SPIFFS] ❌ Błąd inicjalizacji!");
        return;
    }

    initializeLCD();    // Inicjalizacja wyświetlacza LCD
    initializeKeypad(); // Inicjalizacja klawiatury

    Serial.println("✅ System gotowy!");

    //    savePinToJson("1234"); // Zapisujemy testowy PIN
}

void loop()
{
    char key = getPressedKey(); // Pobierz naciśnięty klawisz
    if (key)
    {
        handleKeyPress(key); // Obsłuż naciśnięcie klawisza
        
    }
}
