#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include <esp32-hal-gpio.h>

// Definindo os pinos utilizados
#define LATCH1_PIN 7 // pino de saída de armazenamento do registrador
#define CLOCK1_PIN 6 // pino de clock do registrador
#define DATA1_PIN 5  // pino de dados do registrador
#define DATA2_PIN 4  // pino de dados do registrador
#define DATA3_PIN 18 // pino de dados do registrador
#define DATA4_PIN 2  // pino de dados do registrador
#define DATA5_PIN 3  // pino de dados do registrador
#define DATA6_PIN 1  // pino de dados do registrador

void writeByte(uint8_t data1,
               uint8_t data2,
               uint8_t data3,
               uint8_t data4,
               uint8_t data5,
               uint8_t data6)
{
    digitalWrite(LATCH1_PIN, LOW);
    for (int i = 0; i < 7; i++)
    {
        digitalWrite(CLOCK1_PIN, LOW);

        if (data1 & (1 << i))
        {
            digitalWrite(DATA1_PIN, HIGH);
        }
        else
        {
            digitalWrite(DATA1_PIN, LOW);
        }

        if (data2 & (1 << i))
        {
            digitalWrite(DATA2_PIN, HIGH);
        }
        else
        {
            digitalWrite(DATA2_PIN, LOW);
        }

        if (data3 & (1 << i))
        {
            digitalWrite(DATA3_PIN, HIGH);
        }
        else
        {
            digitalWrite(DATA3_PIN, LOW);
        }

        if (data4 & (1 << i))
        {
            digitalWrite(DATA4_PIN, HIGH);
        }
        else
        {
            digitalWrite(DATA4_PIN, LOW);
        }

        if (data5 & (1 << i))
        {
            digitalWrite(DATA5_PIN, HIGH);
        }
        else
        {
            digitalWrite(DATA5_PIN, LOW);
        }

        if (data6 & (1 << i))
        {
            digitalWrite(DATA6_PIN, HIGH);
        }
        else
        {
            digitalWrite(DATA6_PIN, LOW);
        }

        digitalWrite(CLOCK1_PIN, HIGH);
    }
    digitalWrite(LATCH1_PIN, HIGH);
}

void setup()
{
    pinMode(LATCH1_PIN, OUTPUT);
    pinMode(CLOCK1_PIN, OUTPUT);
    pinMode(DATA1_PIN, OUTPUT);
    pinMode(DATA2_PIN, OUTPUT);
    pinMode(DATA3_PIN, OUTPUT);
    pinMode(DATA4_PIN, OUTPUT);
    pinMode(DATA5_PIN, OUTPUT);
    pinMode(DATA6_PIN, OUTPUT);
}

void app_main()
{
    setup();

    int displaySeteSeg[10] = {

        0b1111110, // DIGITO 0
        0b0110000, // DIGITO 1
        0b1101101, // DIGITO 2
        0b1111001, // DIGITO 3
        0b0110011, // DIGITO 4
        0b1011011, // DIGITO 5
        0b1011111, // DIGITO 6
        0b1110000, // DIGITO 7
        0b1111111, // DIGITO 8
        0b1111011  // DIGITO 9

    };

    int s1 = 7;
    int s2 = 5;
    int s3 = 9;
    int s4 = 5;
    int s5 = 3;
    int s6 = 2;

    while (1)
    {
        writeByte(~displaySeteSeg[s1],
                  ~displaySeteSeg[s2],
                  ~displaySeteSeg[s3],
                  ~displaySeteSeg[s4],
                  ~displaySeteSeg[s5],
                  ~displaySeteSeg[s6]);

        s1++;

        if (s1 == 10)
        {
            s1 = 0;
            s2++;
            if (s2 == 6)
            {
                // s1 = 0;
                s2 = 0;
                s3++;
                if (s3 == 10)
                {
                    // s1 = 0;
                    // s2 = 0;
                    s3 = 0;
                    s4++;
                    if (s4 == 6)
                    {
                        // s1 = 0;
                        // s2 = 0;
                        // s3 = 0;
                        s4 = 0;
                        s5++;

                        if (s6 == 2 && s5 == 4)
                        {
                            s1 = 0;
                            s2 = 0;
                            s3 = 0;
                            s4 = 0;
                            s5 = 0;
                            s6 = 0;
                        }

                        if (s5 == 10)
                        {
                            s5 = 0;
                            s6++;
                        }
                    }
                }
            }
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    return 0;
}