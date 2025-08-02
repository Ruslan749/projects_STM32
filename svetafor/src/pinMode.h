#include "stm32f1xx_hal.h"
/**
 * @brief Инициализация пина PА пинов
 */
void PIN_RED(void)
{
    // Включение тактирования порта A
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0;             // Используем пин 1
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Режим push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // Без подтяжки
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Высокая скорость переключения

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Изначально выключаем светодиод
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
}

void PIN_YELLOW(void)
{
    // Включение тактирования порта A
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_1;             // Используем пин 1
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Режим push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // Без подтяжки
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Высокая скорость переключения

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Изначально выключаем светодиод
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
}
void PIN_BLUE(void)
{
    // Включение тактирования порта A
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_2;             // Используем пин 1
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // Режим push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // Без подтяжки
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Высокая скорость переключения

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Изначально выключаем светодиод
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
}