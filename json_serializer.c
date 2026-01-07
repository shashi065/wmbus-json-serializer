#include "json_serializer.h"
#include <stdio.h>

#define APPEND(fmt, ...) \
    do { \
        int written = snprintf(ptr, remaining, fmt, ##__VA_ARGS__); \
        if (written < 0 || (size_t)written >= remaining) { \
            return JSON_ERR_BUFFER_TOO_SMALL; \
        } \
        ptr += written; \
        remaining -= written; \
    } while (0)

json_status_t serialize_to_json(
    const gateway_payload_t *payload,
    char *out_buffer,
    size_t buffer_size,
    size_t *bytes_written
) {
    if (!payload || !out_buffer || buffer_size == 0) {
        return JSON_ERR_INVALID_ARGUMENT;
    }

    char *ptr = out_buffer;
    size_t remaining = buffer_size;

    APPEND("[{");
    APPEND("\"gatewayId\":\"%s\",", payload->gateway_id);
    APPEND("\"date\":\"%s\",", payload->date);
    APPEND("\"deviceType\":\"%s\",", payload->device_type);
    APPEND("\"interval_minutes\":%u,", payload->interval_minutes);
    APPEND("\"total_readings\":%u,", payload->total_readings);

    APPEND("\"values\":{");
    APPEND("\"device_count\":%zu,", payload->measurements.device_count);
    APPEND("\"readings\":[");

    for (size_t i = 0; i < payload->measurements.device_count; i++) {
        device_reading_t *dev = &payload->measurements.devices[i];

        APPEND("{");
        APPEND("\"media\":\"%s\",", dev->media);
        APPEND("\"meter\":\"%s\",", dev->meter);
        APPEND("\"deviceId\":\"%s\",", dev->device_id);
        APPEND("\"unit\":\"%s\",", dev->unit);
        APPEND("\"data\":[");

        for (size_t j = 0; j < dev->data_count; j++) {
            meter_data_t *d = &dev->data[j];

            APPEND("{");
            APPEND("\"timestamp\":\"%s\",", d->timestamp);
            APPEND("\"meter_datetime\":\"%s\",", d->meter_datetime);
            APPEND("\"total_m3\":%.3f,", d->total_m3);
            APPEND("\"status\":\"%s\"", d->status);
            APPEND("}");

            if (j + 1 < dev->data_count) {
                APPEND(",");
            }
        }

        APPEND("]}");

        if (i + 1 < payload->measurements.device_count) {
            APPEND(",");
        }
    }

    APPEND("]}");
    APPEND("}]");

    if (bytes_written) {
        *bytes_written = (size_t)(ptr - out_buffer);
    }

    return JSON_OK;
}
