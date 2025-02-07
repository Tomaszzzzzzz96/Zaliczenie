package main

import (
  "encoding/json"
  "log"
  "net/http"
  "os"
  "time"
)

var validCardIDs = [...]string{"1234", "5678", "9012", "3456"}
var validPINs = [...]string{"1111", "2222", "3333", "4444"}

type CardRequest struct {
  ID string `json:"id"`
}

type PinRequest struct {
  PIN string `json:"pin"`
}

type ValidationResponse struct {
  Status string `json:"status"`
}

type SensorRequest struct {
  Armed      bool `json:"armed"`
  Motion     bool `json:"motion"`
  Sensitivity int `json:"sensitivity"`
}

var logger *log.Logger = log.New(os.Stdout, "", log.LstdFlags)

func isValidCard(cardID string) bool {
  for _, id := range validCardIDs {
    if id == cardID {
      return true
    }
  }
  return false
}

func isValidPin(pin string) bool {
  for _, validPin := range validPINs {
    if validPin == pin {
      return true
    }
  }
  return false
}

func validateCardHandler(w http.ResponseWriter, r *http.Request) {
  startTime := time.Now()

  var req CardRequest
  if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
    http.Error(w, "Invalid request body", http.StatusBadRequest)
    logger.Printf("Error parsing request: %v", err)
    return
  }

  logger.Printf("Request received - Card ID: %s", req.ID)

  response := ValidationResponse{Status: "bad"}
  if isValidCard(req.ID) {
    response.Status = "good"
  }

  w.Header().Set("Content-Type", "application/json")
  json.NewEncoder(w).Encode(response)

  logger.Printf("Response sent - Card ID: %s, Status: %s, Duration: %v",
    req.ID, response.Status, time.Since(startTime))
}

func validatePinHandler(w http.ResponseWriter, r *http.Request) {
  startTime := time.Now()

  var req PinRequest
  if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
    http.Error(w, "Invalid request body", http.StatusBadRequest)
    logger.Printf("Error parsing request: %v", err)
    return
  }

  logger.Printf("Request received - PIN: ****")  // Don't log actual PIN for security

  if !isValidPin(req.PIN) {
    // Return 403 Forbidden for invalid PIN
    w.Header().Set("Content-Type", "application/json")
    w.WriteHeader(http.StatusForbidden)
    json.NewEncoder(w).Encode(ValidationResponse{Status: "forbidden"})

    logger.Printf("Invalid PIN attempt - Status: forbidden, Duration: %v", time.Since(startTime))
    return
  }

  // Valid PIN
  response := ValidationResponse{Status: "good"}
  w.Header().Set("Content-Type", "application/json")
  json.NewEncoder(w).Encode(response)

  logger.Printf("Response sent - PIN: ****, Status: good, Duration: %v", 
    time.Since(startTime))
}

func sensorHandler(w http.ResponseWriter, r *http.Request) {
  startTime := time.Now()

  var req SensorRequest
  if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
    http.Error(w, "Invalid request body", http.StatusBadRequest)
    logger.Printf("Error parsing request: %v", err)
    return
  }

  logger.Printf("Sensor data received - Armed: %v, Motion: %v, Sensitivity: %d", 
    req.Armed, req.Motion, req.Sensitivity)

  w.Header().Set("Content-Type", "application/json")
  json.NewEncoder(w).Encode(req)

  logger.Printf("Sensor data processed - Duration: %v", time.Since(startTime))
}

func main() {
  logger.Println("Server starting...")
  http.HandleFunc("/validate", validateCardHandler)
  http.HandleFunc("/validate/pin", validatePinHandler)
  http.HandleFunc("/sensor", sensorHandler)
  logger.Println("Server listening on :8080")
  if err := http.ListenAndServe(":8080", nil); err != nil {
    logger.Fatal(err)
  }
}