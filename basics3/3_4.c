#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define ROW1_GPIO GPIO_NUM_9 // Altere para a GPIO correta para a linha 1
#define ROW2_GPIO GPIO_NUM_8 // Altere para a GPIO correta para a linha 2
#define ROW3_GPIO GPIO_NUM_7 // Altere para a GPIO correta para a linha 3
#define ROW4_GPIO GPIO_NUM_6 // Altere para a GPIO correta para a linha 4
#define COL1_GPIO GPIO_NUM_5 // Altere para a GPIO correta para a coluna 1
#define COL2_GPIO GPIO_NUM_4 // Altere para a GPIO correta para a coluna 2
#define COL3_GPIO GPIO_NUM_3 // Altere para a GPIO correta para a coluna 3

const int KEYPAD_ROWS = 4;
const int KEYPAD_COLS = 3;

char keypadKeys[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

gpio_num_t rowPins[] = {
    ROW1_GPIO, ROW2_GPIO, ROW3_GPIO, ROW4_GPIO};

gpio_num_t colPins[] = {
    COL1_GPIO, COL2_GPIO, COL3_GPIO};

int currentKey = -1;

void keypadInit()
{
    for (int i = 0; i < KEYPAD_ROWS; i++)
    {
        gpio_pad_select_gpio(rowPins[i]);
        gpio_set_direction(rowPins[i], GPIO_MODE_OUTPUT);
    }

    for (int i = 0; i < KEYPAD_COLS; i++)
    {
        gpio_pad_select_gpio(colPins[i]);
        gpio_set_direction(colPins[i], GPIO_MODE_INPUT);
        gpio_set_pull_mode(colPins[i], GPIO_PULLUP_ONLY);
    }
}

char keypadGetKey()
{
    char key = '\0';

    for (int r = 0; r < KEYPAD_ROWS; r++)
    {
        gpio_set_level(rowPins[r], 0);

        for (int c = 0; c < KEYPAD_COLS; c++)
        {
            if (gpio_get_level(colPins[c]) == 0)
            {
                key = keypadKeys[r][c];
                break;
            }
        }

        gpio_set_level(rowPins[r], 1);
    }

    return key;
}

void app_main()
{
    keypadInit();

    while (1)
    {
        char key = keypadGetKey();

        if (key != '\0' && key != currentKey)
        {
            printf("Tecla pressionada: %c\n", key);
            currentKey = key;
        }

        vTaskDelay(100 / portTICK_PERIOD_MS); // Pequena pausa
    }
}
