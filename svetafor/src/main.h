#include "pinMode.h"
#include <stdbool.h>
/**
 * @brief Определение enum с режимами работы
 */
typedef enum {
  MODE_AUTO, // Автоматический режим
  MODE_MNT   // Ручной режим
} SystemMode;

// Прототипы функций
void SystemClock_Config(
    void); // функция системных настроек контролера и конфигураций
void Error_Handler(void); // функция обработчика ошибок
void PIN_LED(void);       // функция реализации светодиодов
void PIN_BUTTON(void);    // функция инициализации кнопок

void setupTrafficLightAUTO(
    void); // функция для автоматического включения режима светофора
void setupTrafficLightMNT(
    void);            // функция для ручного включения режима светофора
void setupMode(void); // функция обработки режима работы
void resetTrafficLightState(void); // функция сброса состояния светодиодов

// глобальные переменные
bool flag = true;   // флаг завершения работы мигания синего/зеленого светодиода
bool pinUp = false; //
SystemMode currentMode = MODE_AUTO; // Текущий режим (по умолчанию EMPTY)
uint32_t lastDebounceTime = 0;      // последнее время срабатывания кнопки

const uint32_t debounceDelay = 50; // время антидребезга в мс

/**
 * @brief System Clock Configuration
 *        Используем внутренний генератор 8MHz (HSI)
 *        Цель: SYSCLK = 64MHz
 */
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  // Настройка источника тактирования
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16; // 8MHz / 2 * 16 = 64MHz
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  // Настройка делителей частоты
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // HCLK = 64MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  // APB1 = 32MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  // APB2 = 64MHz

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

/**
 * @brief Обработчик ошибок
 */
void Error_Handler(void) {
  while (1) {
    // Аварийное мигание PB2 при ошибке
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
    HAL_Delay(100);
  }
}
/**
 * @brief Обработчики прерываний (для каждой кнопки должен быть отдельный
 * обработчик)
 */
void EXTI3_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3); }

void EXTI4_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4); }
/**
 * @brief Функция вызывается автоматически из обработчика прерывания,
 *  когда происходит событие на линии внешнего прерывания (EXTI)
 * для определённого пина (переопределенная из библиотеки HAL).
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  uint32_t currentTime = HAL_GetTick();

  // Защита от дребезга
  if ((currentTime - lastDebounceTime) >= debounceDelay) {
    lastDebounceTime = currentTime;

    if (GPIO_Pin == GPIO_PIN_3) {
      currentMode = MODE_AUTO; // Активируем режим AUTO
    } else if (GPIO_Pin == GPIO_PIN_4) {
      if (currentMode == MODE_MNT) {
        pinUp = true;
      }
      currentMode = MODE_MNT; // Активируем режим MNT
    }
  }
}

/**
 * @brief Обязательные обработчики прерываний
 */
void SysTick_Handler(void) { HAL_IncTick(); }

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
  while (1) {
    // Аварийное мигание светодиодом
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
    HAL_Delay(100);
  }
}
#endif