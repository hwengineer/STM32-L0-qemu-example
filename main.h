#ifndef MAIN_H
#define MAIN_H

#include "stm32l0xx_hal.h"

#define LED_PIN                                GPIO_PIN_5
#define LED_GPIO_PORT                          GPIOA
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOA_CLK_ENABLE()

#define LED_PIN2                                GPIO_PIN_7
#define LED_GPIO_PORT2                          GPIOB
#define LED_GPIO_CLK_ENABLE2()                  __HAL_RCC_GPIOB_CLK_ENABLE()

#endif // MAIN_H
