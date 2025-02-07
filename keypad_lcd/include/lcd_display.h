#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Definicja pinów SPI dla wyświetlacza
#define TFT_CS 18
#define TFT_DC 5
#define TFT_RST 17
#define TFT_MOSI 21
#define TFT_SCLK 19
#define TFT_BL 16

// Deklaracja obiektu wyświetlacza
extern Adafruit_ILI9341 tft;

// Deklaracja funkcji inicjalizującej wyświetlacz LCD
void initializeLCD();
// Deklaracja funkcji wyświetlającej PIN na ekranie LCD
void displayPinOnLCD(const String &pin, uint16_t color = ILI9341_WHITE);
// Deklaracja funkcji wyświetlającej błąd na ekranie LCD
void displayErrorOnLCD();
// Deklaracja funkcji wyświetlającej sukces na ekranie LCD
void displaySuccessOnLCD();

#endif // LCD_DISPLAY_H
