#pragma once

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

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
#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET

#define UART_RX__SZ 64
#define UART_TX__SZ 64
#define UART_DMA_WRITE_PTR ((UART_RX__SZ - huart1.hdmarx->Instance->CNDTR) & (UART_RX__SZ - 1)) 
#define HEADER_SIZE 4
#define HEADER_MASK (uint32_t)0xFFFFFD00

typedef enum {false, true} bool;

I2C_HandleTypeDef hi2c2;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_I2C2_Init(void);
void MX_USART1_UART_Init(void);
