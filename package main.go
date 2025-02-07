package main

import (
  "encoding/json"
  "log"
  "net/http"
  "os"
  "time"
)

var validCardIDs = [...]string{"1234", "5678", "9012", "3456"}

type CardRequest struct {
  ID string `json:"id"`
}

type CardResponse struct {
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

func validateCardHandler(w http.ResponseWriter, r *http.Request) {
  startTime := time.Now()

  var req CardRequest
  if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
    http.Error(w, "Invalid request body", http.StatusBadRequest)
    logger.Printf("Error parsing request: %v", err)
    return
  }

  logger.Printf("Request received - Card ID: %s", req.ID)

  // Updated validation using helper function
  response := CardResponse{Status: "bad"}
  if isValidCard(req.ID) {
    response.Status = "good"
  }

  w.Header().Set("Content-Type", "application/json")
  json.NewEncoder(w).Encode(response)

  logger.Printf("Response sent - Card ID: %s, Status: %s, Duration: %v",
    req.ID, response.Status, time.Since(startTime))
}

func sensorHandler(w http.ResponseWriter, r *http.Request) {
  startTime := time.Now()

  var req SensorRequest
  if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
    http.Error(w, "Invalid request body", http.StatusBadRequest)
    logger.Printf("Error parsing request: %v", err)
    return
  }

  logger.Printf("Sensor data received - Armed: %v, Motion: %v, Sensitivity: %d", req.Armed, req.Motion, req.Sensitivity)

  // Here you can add logic to process the sensor data if needed

  w.Header().Set("Content-Type", "application/json")
  json.NewEncoder(w).Encode(req)

  logger.Printf("Sensor data processed - Duration: %v", time.Since(startTime))
}

func main() {
  logger.Println("Server starting...")
  http.HandleFunc("/validate", validateCardHandler)
  http.HandleFunc("/sensor", sensorHandler)
  logger.Println("Server listening on :8080")
  if err := http.ListenAndServe(":8080", nil); err != nil {
    logger.Fatal(err)
  }
}