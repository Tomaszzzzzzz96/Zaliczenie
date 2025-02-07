#include "lcd_display.h"

// Inicjalizacja wyświetlacza
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// Funkcja inicjalizująca wyświetlacz LCD
void initializeLCD()
{
    tft.begin();
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    Serial.println("LCD Initialized");

    // Początkowy ekran - PIN + instrukcje
    tft.setCursor(10, 50);
    tft.print("PIN: ");

    tft.setCursor(10, 100);
    tft.print("* - DELETE");

    tft.setCursor(10, 120);
    tft.print("# - ACCEPT");
}

// Funkcja wyświetlająca PIN na ekranie LCD
void displayPinOnLCD(const String &pin, uint16_t color)
{
    // Zmieniamy kolor PIN-u
    tft.setTextColor(color);
    tft.fillRect(10, 50, 200, 20, ILI9341_BLACK); // Czyszczenie miejsca
    tft.setCursor(10, 50);
    tft.print("PIN: ");

    // Wyświetlamy wpisany PIN jako gwiazdki
    tft.setCursor(60, 50);
    for (size_t i = 0; i < pin.length(); i++)
    {
        tft.print('*');
    }
}

// Funkcja wyświetlająca błąd na ekranie LCD
void displayErrorOnLCD()
{
    // Wyświetlamy "Błędny PIN!" w miejscu "PIN: "
    tft.fillRect(10, 50, 200, 20, ILI9341_BLACK);
    tft.setTextColor(ILI9341_RED);
    tft.setCursor(10, 50);
    tft.print("Błędny PIN!");

    // Oczekiwanie 2 sekundy
    delay(2000);

    // Resetowanie ekranu, przywrócenie "PIN: " na biało
    tft.fillRect(10, 50, 200, 20, ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 50);
    tft.print("PIN: ");
}

// Funkcja wyświetlająca sukces na ekranie LCD
void displaySuccessOnLCD()
{
    // "PIN:" w kolorze zielonym
    tft.setTextColor(ILI9341_GREEN);
    tft.fillRect(10, 50, 200, 20, ILI9341_BLACK);
    tft.setCursor(10, 50);
    tft.print("PIN: OK");

    // Czekamy 2 sekundy, zanim ekran wróci do białego
    delay(2000);
    tft.fillRect(10, 50, 200, 20, ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 50);
    tft.print("PIN: ");
}
