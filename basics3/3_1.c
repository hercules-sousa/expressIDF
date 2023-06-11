#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PIN 9

static const char *TAG = "LED WITH NO DEBOUNCE";

void app_main()
{
    gpio_set_direction(PIN, GPIO_MODE_INPUT);
    int count = 0;
    int previous_state = 0;
    int state = previous_state;

    while (1)
    {
        state = gpio_get_level(PIN);

        if (state != previous_state)
        {
            count++;
            previous_state = state;
        }

        ESP_LOGE(TAG, "Count = %d", count);
    }
}