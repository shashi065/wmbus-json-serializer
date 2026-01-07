#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    JSON_OK = 0,
    JSON_ERR_BUFFER_TOO_SMALL,
    JSON_ERR_INVALID_ARGUMENT
} json_status_t;

#define MAX_DEVICES     4
#define MAX_DATA_POINTS 4

typedef struct {
    const char *timestamp;
    const char *meter_datetime;
    double total_m3;
    const char *status;
} meter_data_t;

typedef struct {
    const char *media;
    const char *meter;
    const char *device_id;
    const char *unit;
    size_t data_count;
    meter_data_t data[MAX_DATA_POINTS];
} device_reading_t;

typedef struct {
    size_t device_count;
    device_reading_t devices[MAX_DEVICES];
} measurement_block_t;

typedef struct {
    const char *gateway_id;
    const char *date;
    const char *device_type;
    uint32_t interval_minutes;
    uint32_t total_readings;
    measurement_block_t measurements;
} gateway_payload_t;

json_status_t serialize_to_json(
    const gateway_payload_t *payload,
    char *out_buffer,
    size_t buffer_size,
    size_t *bytes_written
);

#endif
