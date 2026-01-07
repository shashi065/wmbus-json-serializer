#include <stdio.h>
#include "json_serializer.h"

int main(void) {
    gateway_payload_t payload = {
        .gateway_id = "gateway_1234",
        .date = "1970-01-01",
        .device_type = "stromleser",
        .interval_minutes = 15,
        .total_readings = 1,
        .measurements = {
            .device_count = 1,
            .devices = {
                {
                    .media = "water",
                    .meter = "waterstarm",
                    .device_id = "stromleser_50898527",
                    .unit = "m3",
                    .data_count = 1,
                    .data = {
                        {
                            .timestamp = "1970-01-01 00:00",
                            .meter_datetime = "1970-01-01 00:00",
                            .total_m3 = 107.752,
                            .status = "OK"
                        }
                    }
                }
            }
        }
    };

    char buffer[1024];
    size_t written;

    if (serialize_to_json(&payload, buffer, sizeof(buffer), &written) == JSON_OK) {
        printf("%s\n", buffer);
    }

    return 0;
}
