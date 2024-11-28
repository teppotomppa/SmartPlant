package data

import (
	"context"
	"encoding/json"
	"goapi/internal/api/repository/models"
	service "goapi/internal/api/service/data"
	"log"
	"net/http"
	"time"
)

// PostHandler handles the POST request to /data
// User sends a POST request to /data with a JSON payload in the request body
// curl -X POST http://127.0.0.1:8080/data -i -u admin:password -H "Content-Type: application/json" -d '{"moisture_level": 40, "date_time": "2024-11-28T12:00:00Z"}'
func PostHandler(w http.ResponseWriter, r *http.Request, logger *log.Logger, ds service.DataService) {
	var data models.Data

	// Decode the JSON payload from the request body into the data struct
	if err := json.NewDecoder(r.Body).Decode(&data); err != nil {
		// This is a user error: format of body is invalid, respond with a 400 status code
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte(`{"error": "Invalid request data. Please check your input."}`))
		return
	}

	// Check if the moisture level is provided and valid
	if data.MoistureLevel == 0 {
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte(`{"error": "Moisture level is missing or invalid."}`))
		return
	}

	ctx, cancel := context.WithTimeout(r.Context(), 2*time.Second)
	defer cancel()

	// Try to create the data in the database
	if err := ds.Create(&data, ctx); err != nil {
		switch err.(type) {
		case service.DataError:
			// If the error is a DataError, handle it as a client error
			w.WriteHeader(http.StatusBadRequest)
			w.Write([]byte(`{"error": "` + err.Error() + `"}`))
			return
		default:
			// If it is not a DataError, handle it as a server error
			logger.Println("Error creating data:", err, data)
			http.Error(w, "Internal server error.", http.StatusInternalServerError)
			return
		}
	}

	// Check moisture level and decide whether to water or not
	var action string
	if data.MoistureLevel < data.MoistureThreshold { // Example threshold for moisture level
		action = "water_on"
		// Optionally trigger watering action, e.g., sending a request to Arduino (optional)
	} else {
		action = "water_off"
		// Optionally stop watering (optional)
	}

	// Send back a response with the action (e.g., "water_on" or "water_off")
	response := struct {
		Action string `json:"action"`
	}{
		Action: action,
	}

	// Respond with the action in JSON format
	w.Header().Set("Content-Type", "application/json")
	if err := json.NewEncoder(w).Encode(response); err != nil {
		logger.Println("Error encoding response:", err)
		http.Error(w, "Internal server error.", http.StatusInternalServerError)
	}
}
