#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include <esp32-hal-gpio.h>

// Definindo os pinos utilizados
#define LATCH_PIN 7 // pino de saída de armazenamento do registrador
#define CLOCK_PIN 6 // pino de clock do registrador
#define DATA_PIN 5  // pino de dados do registrador

void writeByte(uint8_t data)
{
    digitalWrite(LATCH_PIN, LOW);
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(CLOCK_PIN, LOW);
        if (data & (1 << i))
        {
            digitalWrite(DATA_PIN, HIGH);
        }
        else
        {
            digitalWrite(DATA_PIN, LOW);
        }
        digitalWrite(CLOCK_PIN, HIGH);
    }
    digitalWrite(LATCH_PIN, HIGH);
}

void setup()
{
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
}

void app_main()
{
    setup();

    uint8_t data = 0b10001001;
    writeByte(data);

    while (1)
    {
        // loop infinito
    }
    return 0;
}