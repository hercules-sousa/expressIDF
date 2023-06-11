#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp32-hal-ledc.h>

#define LED_PIN 4
#define PWM_FREQ 1000
#define PWM_RESOLUTION 8

void app_main()
{
    ledcSetup(0, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(LED_PIN, 0);

    for (int i = 256 * 0.1; i < 256 * 0.7; i++)
    {
        ledcWrite(0, i);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}