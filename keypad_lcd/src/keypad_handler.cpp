#include "keypad_handler.h"
#include "lcd_display.h"
#include "json_handler.h"
#include "server_handler.h"
#include <Arduino.h>

// Definicja klawiszy na klawiaturze
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Definicja pinów dla wierszy i kolumn klawiatury
byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {26, 25, 33, 32};

// Inicjalizacja klawiatury
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String enteredPin = "";
char lastKey = '\0';

// Funkcja inicjalizująca klawiaturę
void initializeKeypad()
{
    Serial.println("🔢 Keypad initialized");
    initializeLCD();
}

// Funkcja zwracająca naciśnięty klawisz
char getPressedKey()
{
    return keypad.getKey();
}

// Funkcja obsługująca naciśnięcia klawiszy
void handleKeyPress(char key)
{
    if (key)
    {
        lastKey = key;

        if (key == '#')
        {
            if (enteredPin.length() == 4)
            {
                Serial.println("🔑 PIN Entered: " + enteredPin);
                // String storedPin = readPinFromJson();
                bool success = sendJsonToServer(enteredPin);
                if (success)
                {
                    Serial.println("✅ Dostęp przyznany!");
                    displaySuccessOnLCD();
                }
                else
                {
                    Serial.println("❌ Niepoprawny PIN!");
                    displayErrorOnLCD();
                }

                delay(2000);
                enteredPin = "";
                displayPinOnLCD(enteredPin);
            }
            else
            {
                Serial.println("⚠️ PIN musi mieć 4 cyfry!");
                displayErrorOnLCD();
                delay(2000);
                enteredPin = "";
                displayPinOnLCD(enteredPin);
            }
        }
        else if (key == '*')
        {
            enteredPin = "";
            Serial.println("🔄 PIN Cleared");
            displayPinOnLCD(enteredPin);
        }
        else
        {
            if (enteredPin.length() < 4)
            {
                enteredPin += key;
                displayPinOnLCD(enteredPin);
                Serial.println("📌 Current PIN: " + enteredPin);
            }
            else
            {
                Serial.println("⚠️ PIN za długi! Reset.");
                displayErrorOnLCD();
                delay(2000);
                enteredPin = "";
                displayPinOnLCD(enteredPin);
            }
        }
    }
    else if (!key)
    {
        lastKey = '\0';
    }
}
