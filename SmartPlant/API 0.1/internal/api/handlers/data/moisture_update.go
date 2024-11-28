package data

import (
	"encoding/json"
	service "goapi/internal/api/service/data"
	"log"
	"net/http"
)

// MoistureUpdateHandler updates the moisture threshold in the database.
func MoistureUpdateHandler(w http.ResponseWriter, r *http.Request, logger *log.Logger, ds service.DataService) {
	var updateRequest struct {
		MoistureThreshold int `json:"moisture_threshold"`
	}

	// Decode the request body into the struct
	if err := json.NewDecoder(r.Body).Decode(&updateRequest); err != nil {
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte(`{"error": "Invalid request body"}`))
		return
	}

	// Fetch data and update moisture threshold
	data, err := ds.ReadOne(1, r.Context()) // Use the relevant ID, or dynamic retrieval if needed
	if err != nil {
		logger.Println("Error fetching data:", err)
		http.Error(w, "Internal server error", http.StatusInternalServerError)
		return
	}

	// Update the moisture threshold
	data.MoistureThreshold = updateRequest.MoistureThreshold

	// Save the updated data back to the database
	if _, err := ds.Update(data, r.Context()); err != nil {
		logger.Println("Error updating data:", err)
		http.Error(w, "Failed to update moisture threshold", http.StatusInternalServerError)
		return
	}

	// Success response
	w.WriteHeader(http.StatusOK)
	w.Write([]byte(`{"message": "Moisture threshold updated successfully"}`))
}
