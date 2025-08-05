#include "main.h"

int main(void)
{
    // Инициализация HAL
    HAL_Init();

    // Настройка системного тактирования
    SystemClock_Config();

    // Инициализация пинов и кнопок
    PIN_LED();
    PIN_BUTTON();

    while (1)
    {
        setupMode();
    }
}
void setupTrafficLightMNT(void)
{
    if (flag)
    {
        // Включение светодиода A0 (RED)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
        HAL_Delay(2000);
        // Проверяем что кнопка нажата
        if (pinUp)
        {
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
                    pinUp = false;
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
                }
            }
        }

        HAL_Delay(10); // Небольшая задержка для снижения нагрузки
    }
}
void setupTrafficLightAUTO(void)
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

void setupMode(void)
{
    // Обработка логики для текущего режима
    switch (currentMode)
    {
    case MODE_AUTO:
        // Действия в автоматическом режиме
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET); // Светодиод постоянно горит
        setupTrafficLightAUTO();
        break;

    case MODE_MNT:
        // Действия в ручном режиме
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2); // Мигание светодиода
        HAL_Delay(250);                        // Задержка для мигания
        setupTrafficLightMNT();
        break;
    }

    HAL_Delay(10); // Небольшая задержка для снижения нагрузки
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t currentTime = HAL_GetTick();

    // Защита от дребезга
    if ((currentTime - lastDebounceTime) >= debounceDelay)
    {
        lastDebounceTime = currentTime;

        if (GPIO_Pin == GPIO_PIN_3)
        {
            currentMode = MODE_AUTO; // Активируем режим AUTO
        }
        else if (GPIO_Pin == GPIO_PIN_4)
        {
            if (currentMode == MODE_MNT)
            {
               pinUp = true;
            }
            currentMode = MODE_MNT; // Активируем режим MNT
            
        }
    }
}