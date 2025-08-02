#include "main.h"

int main(void)
{
    // Инициализация HAL
    HAL_Init();

    // Настройка системного тактирования
    SystemClock_Config();

    // Инициализация пина PA пинов
    PIN_RED();
    PIN_YELLOW();
    PIN_BLUE();

    while (1)
    {
        setupSvetafor();
    }
}

void setupSvetafor(void)
{
    if (flag)
    {
        // Включение светодиода A0 (RED)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
        HAL_Delay(2000);

        // Выключение светодиода A0 (RED)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
        HAL_Delay(500);

        // Включение светодиода A2 (YELLOW)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
        HAL_Delay(2000);

        // Выключение светодиода A2 (YELLOW)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_Delay(500);

        // Включение светодиода A1 (BLUE)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
        HAL_Delay(2000);
    }

    flag = false;
    for (size_t i = 0; i <= 3; i++)
    {
        // Выключение светодиода A1 (BLUE)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
        HAL_Delay(300);

        // Включение светодиода A1 (BLUE)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
        HAL_Delay(300);

        if (i == 3)
        {
            flag = true;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
        }
    }
}
