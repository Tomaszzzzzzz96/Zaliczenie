# 📂 Folder `src` – Implementacja funkcjonalności

Folder `src` zawiera pliki źródłowe (`.cpp`), które implementują funkcjonalność systemu obsługi pinpada i wyświetlacza LCD. Każdy plik odpowiada za określony moduł projektu.

---

## 📌 Przegląd plików

### 🔢 `keypad_handler.cpp`

Obsługa klawiatury numerycznej (pinpad):

- **`initializeKeypad()`** – Inicjalizuje klawiaturę i wyświetlacz LCD.
- **`getPressedKey()`** – Pobiera naciśnięty klawisz.
- **`handleKeyPress(char key)`** – Obsługuje logikę zdarzeń:
  - Akceptacja PIN-u (`#`).
  - Reset PIN-u (`*`).
  - Wpisywanie PIN-u (cyfry).

---

### 🖥️ `lcd_display.cpp`

Obsługa wyświetlacza LCD:

- **`initializeLCD()`** – Konfiguruje ekran ILI9341, ustawia komunikaty.
- **`displayPinOnLCD(const String &pin, uint16_t color)`** – Wyświetla PIN jako gwiazdki.
- **`displayErrorOnLCD()`** – Komunikat błędu „Błędny PIN!”.
- **`displaySuccessOnLCD()`** – Komunikat potwierdzenia „PIN: OK”.

---

### 🗄️ `json_handler.cpp`

Obsługa plików JSON na SPIFFS:

- **`savePinToJson(const String &pin)`** – Zapisuje PIN w pliku `/pin_data.json`.
- **`readPinFromJson()`** – Odczytuje PIN z pliku, tworzy domyślny PIN, jeśli plik nie istnieje.
- **`sendJsonToServer()`** – Wysyła plik do serwera.

---

### 🌐 `wifi_handler.cpp`

Obsługa połączenia WiFi:

- **`setupWiFi()`** – Łączy się z siecią WiFi, wyświetla adres IP.

---

### 📡 `server_handler.cpp`

Komunikacja z serwerem:

- **`testServerConnection()`** – Testuje połączenie z serwerem.
- **`sendJsonToServer()`** – Wysyła dane JSON do serwera.

---

### 🚀 `main.cpp`

Główna pętla programu:

- **`setup()`**:
  - Inicjalizuje WiFi, SPIFFS, LCD i klawiaturę.
  - Ustawia domyślny PIN.
- **`loop()`**:
  - Obsługuje wpisywanie PIN-u i logikę systemu.

---

## 📖 Struktura kodu

Kod został podzielony na moduły, które komunikują się ze sobą:

1. **Klawiatura (`keypad_handler.cpp`)** obsługuje wejście użytkownika.
2. **Wyświetlacz (`lcd_display.cpp`)** wyświetla PIN i komunikaty.
3. **Plik JSON (`json_handler.cpp`)** przechowuje i wysyła PIN.
4. **WiFi (`wifi_handler.cpp`)** zapewnia łączność z siecią.
5. **Serwer (`server_handler.cpp`)** odbiera dane PIN.

---
