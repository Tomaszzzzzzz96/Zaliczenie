#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <Arduino.h>

// Deklaracja funkcji zapisującej PIN do pliku JSON
void savePinToJson(const String &pin);
// Deklaracja funkcji odczytującej PIN z pliku JSON
String readPinFromJson();

#endif // JSON_HANDLER_H
