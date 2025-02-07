# 📂 Folder `include` – Opis plików nagłówkowych

Folder `include` zawiera nagłówki definiujące funkcjonalność poszczególnych modułów projektu. Każdy z tych plików odpowiada za określony aspekt działania systemu.

---

## 📌 Przegląd plików

### 🔢 `keypad_handler.h`

Moduł obsługi klawiatury numerycznej (pinpad):

- **`initializeKeypad()`** – Inicjalizuje klawiaturę 4x4.
- **`getPressedKey()`** – Zwraca naciśnięty klawisz.
- **`handleKeyPress(char key)`** – Obsługuje logikę zdarzeń po naciśnięciu klawisza.

---

### 🖥️ `lcd_display.h`

Moduł obsługi wyświetlacza LCD z kontrolerem ILI9341:

- **`initializeLCD()`** – Inicjalizuje wyświetlacz.
- **`displayPinOnLCD(const String &pin, uint16_t color)`** – Wyświetla PIN na ekranie.
- **`displayErrorOnLCD()`** – Wyświetla komunikat błędu.
- **`displaySuccessOnLCD()`** – Wyświetla komunikat sukcesu.

---

### 🌐 `wifi_handler.h`

Moduł obsługi połączenia WiFi:

- **`setupWiFi()`** – Inicjalizuje połączenie WiFi.

---

### 📡 `server_handler.h`

Moduł obsługi komunikacji z serwerem:

- **`sendJsonToServer()`** – Wysyła dane w formacie JSON do serwera.

---

### 🗄️ `json_handler.h`

Moduł obsługi plików JSON:

- **`savePinToJson(const String &pin)`** – Zapisuje PIN do pliku JSON.
- **`readPinFromJson()`** – Odczytuje PIN z pliku JSON.

---

## 📖 Struktura kodu

Każdy plik nagłówkowy w folderze `include` zawiera deklaracje funkcji, które są implementowane w odpowiadających im plikach źródłowych `.cpp`. Pliki te definiują funkcjonalności używane w głównym kodzie programu.

---
