/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 2 */
#define JOYSTICK_SW_PIN GPIO_PIN_5
#define JOYSTICK_SW_PORT GPIOB

void Joystick_Init(void) {
    // 初始化 GPIO 用于 SW 输入
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();  // 启用 GPIOB 的时钟

    GPIO_InitStruct.Pin = JOYSTICK_SW_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // 设置为输入模式
    GPIO_InitStruct.Pull = GPIO_PULLUP;  // 启用上拉电阻
    HAL_GPIO_Init(JOYSTICK_SW_PORT, &GPIO_InitStruct);
}
/* USER CODE END 2 */
