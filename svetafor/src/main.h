
#include "pinMode.h"
#include <stdbool.h>

// Прототипы функций
void SystemClock_Config(void);
void Error_Handler(void);
void PIN_2_INIT(void);
void PIN_RED(void);
void PIN_BLUE(void);
void PIN_YELLOW(void);

void setupSvetafor(void); // функция для включения режима светофора

// прототипы переменных
bool flag = true;

/**
 * @brief System Clock Configuration
 *        Используем внутренний генератор 8MHz (HSI)
 *        Цель: SYSCLK = 64MHz
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Настройка источника тактирования
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16; // 8MHz / 2 * 16 = 64MHz
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    // Настройка делителей частоты
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // HCLK = 64MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  // APB1 = 32MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  // APB2 = 64MHz

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Обработчик ошибок
 */
void Error_Handler(void)
{
    while (1)
    {
        // Аварийное мигание PB2 при ошибке
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
        HAL_Delay(100);
    }
}

// Обязательные обработчики прерываний
void SysTick_Handler(void)
{
    HAL_IncTick();
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    while (1)
    {
        // Аварийное мигание светодиодом
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
        HAL_Delay(100);
    }
}
#endif