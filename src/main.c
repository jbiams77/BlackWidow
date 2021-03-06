/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port_handler.h"
#include "packet_handler.h"
#include <stdint.h>
#include "utility.h"
#include "flash.h"


MessageQueue *message;


/* Private function prototypes -----------------------------------------------*/


/* MAIN ------------------------------------------------------------*/
int main(void)
{
  
  message = constructMessage();
  /* Initialize parameters by pulling from Flash */
  /*** Initialization ***/
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
 	DWT_Init();
	DRV8825_initStepper();
  AS5600_SetZero();
  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, 0);
  UART_DMA_Init();
  //initialize_stored_parameters();

  while(1) {
    //transmit_buffer(array, sizeof(array));
    //HAL_Delay(5000);
    process_queue();
  }
}


