#include "stm32f1xx_hal.h"
/**
 * @brief Инициализация пина PА пинов
 */
void PIN_LED(void)
{
    // Включение тактирования порта A0 (RED)
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0;             // Используем пин 0
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Режим push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // Без подтяжки
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Высокая скорость переключения

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Изначально выключаем светодиод
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

    //------------------------------------------------------------------------------------------
    // Включение тактирования порта A1(YELLOW)
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_1;             // Используем пин 1
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Режим push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // Без подтяжки
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Высокая скорость переключения

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Изначально выключаем светодиод
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

    //------------------------------------------------------------------------------------------
    // Включение тактирования порта A2(BLUE)
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_2;             // Используем пин 2
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Режим push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // Без подтяжки
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Высокая скорость переключения

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Изначально выключаем светодиод
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);

    //------------------------------------------------------------------------------------------
    // Включение тактирования порта B2(пин контроллера)
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_2;             // Используем пин 2
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Режим push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // Без подтяжки
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Высокая скорость переключения

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Изначально выключаем светодиод
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
}

void PIN_BUTTON(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Настройка PA3 (кнопка 1)
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Настройка PA4 (кнопка 2)
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Настройка приоритета прерываний
    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
    HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}
