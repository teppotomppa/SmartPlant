package models

import "context"

type Data struct {
	ID                int    `json:"id"`
	DateTime          string `json:"date_time"`
	MoistureLevel     int    `json:"moisture_level"`     //new field for moisture level
	MoistureThreshold int    `json:"moisture_threshold"` //new field for moisture threshold
}

type DataRepository interface {
	Create(Data *Data, ctx context.Context) error
	ReadOne(id int, ctx context.Context) (*Data, error)
	ReadMany(page int, rowsPerPage int, ctx context.Context) ([]*Data, error)
	Update(data *Data, ctx context.Context) (int64, error)
	Delete(data *Data, ctx context.Context) (int64, error)
}
