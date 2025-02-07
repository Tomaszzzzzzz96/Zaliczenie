#ifndef KEYPAD_HANDLER_H
#define KEYPAD_HANDLER_H

#include <Keypad.h>

// Definicja liczby wierszy i kolumn klawiatury
#define ROWS 4
#define COLS 4

// Deklaracja zmiennych klawiatury
extern char keys[ROWS][COLS];
extern byte rowPins[ROWS];
extern byte colPins[COLS];
extern Keypad keypad;

// Deklaracja funkcji inicjalizującej klawiaturę
void initializeKeypad();
// Deklaracja funkcji zwracającej naciśnięty klawisz
char getPressedKey();
// Deklaracja funkcji obsługującej naciśnięcia klawiszy
void handleKeyPress(char key);

#endif // KEYPAD_HANDLER_H
