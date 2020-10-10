/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FAN_Pin GPIO_PIN_2
#define FAN_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOA
#define M2_Pin GPIO_PIN_13
#define M2_GPIO_Port GPIOB
#define M1_Pin GPIO_PIN_14
#define M1_GPIO_Port GPIOB
#define M0_Pin GPIO_PIN_15
#define M0_GPIO_Port GPIOB
#define STEP_Pin GPIO_PIN_8
#define STEP_GPIO_Port GPIOA
#define ENABLE_Pin GPIO_PIN_9
#define ENABLE_GPIO_Port GPIOA
#define STEP_DIR_Pin GPIO_PIN_10
#define STEP_DIR_GPIO_Port GPIOA
#define DATA_DIR_Pin GPIO_PIN_5
#define DATA_DIR_GPIO_Port GPIOB

#define BUFFER_SIZE 8
#define HEADER1 0
#define HEADER2 1
#define HEADER3 2
#define RESERVED 3
#define PACKET_ID  4
#define LENGTH_LOW 5
#define LENGTH_HIGH 6



#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
