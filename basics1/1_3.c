#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include <esp32-hal-gpio.h>

// Definindo os pinos utilizados
#define A_PIN 9
#define B_PIN 8
#define C_PIN 7
#define D_PIN 6
#define E_PIN 5
#define F_PIN 18
#define G_PIN 4

#define delay(value) vTaskDelay(value / portTICK_PERIOD_MS)

void setup()
{
    pinMode(A_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);
    pinMode(C_PIN, OUTPUT);
    pinMode(D_PIN, OUTPUT);
    pinMode(E_PIN, OUTPUT);
    pinMode(F_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
}

void app_main()
{
    setup();

    digitalWrite(A_PIN, HIGH);
    digitalWrite(B_PIN, HIGH);
    digitalWrite(C_PIN, HIGH);
    digitalWrite(D_PIN, HIGH);
    digitalWrite(E_PIN, HIGH);
    digitalWrite(F_PIN, HIGH);
    digitalWrite(G_PIN, HIGH);

    int displaySeteSeg[10][7] = {

        {1, 1, 1, 1, 1, 1, 0}, // DIGITO 0
        {0, 1, 1, 0, 0, 0, 0}, // DIGITO 1
        {1, 1, 0, 1, 1, 0, 1}, // DIGITO 2
        {1, 1, 1, 1, 0, 0, 1}, // DIGITO 3
        {0, 1, 1, 0, 0, 1, 1}, // DIGITO 4
        {1, 0, 1, 1, 0, 1, 1}, // DIGITO 5
        {1, 0, 1, 1, 1, 1, 1}, // DIGITO 6
        {1, 1, 1, 0, 0, 0, 0}, // DIGITO 7
        {1, 1, 1, 1, 1, 1, 1}, // DIGITO 8
        {1, 1, 1, 1, 0, 1, 1}  // DIGITO 9

    };

    int n = 0;

    while (1)
    {
        digitalWrite(A_PIN, !displaySeteSeg[n][0]);
        digitalWrite(B_PIN, !displaySeteSeg[n][1]);
        digitalWrite(C_PIN, !displaySeteSeg[n][2]);
        digitalWrite(D_PIN, !displaySeteSeg[n][3]);
        digitalWrite(E_PIN, !displaySeteSeg[n][4]);
        digitalWrite(F_PIN, !displaySeteSeg[n][5]);
        digitalWrite(G_PIN, !displaySeteSeg[n][6]);

        delay(2000);
        n++;

        if (n == 10)
        {
            n = 0;
        }
    }
    return 0;
}