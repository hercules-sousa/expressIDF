#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define BUTTON_GPIO_PIN 9
#define DEBOUNCE_MS 100
static const char *TAG = "GPIO_INPUT";

void app_main()
{
    gpio_set_direction(BUTTON_GPIO_PIN, GPIO_MODE_INPUT);
    int counter = 0;
    int state = 1;
    int previous_state = 1;

    while (1)
    {
        state = gpio_get_level(BUTTON_GPIO_PIN);

        if (state != previous_state)
        {
            previous_state = state;
            if (!state)
            {
                counter++;
            }
        }

        ESP_LOGE(TAG, "Counter = %d", counter);
    }
}
