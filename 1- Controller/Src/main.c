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
#include <stdint.h>
#include "utility.h"
#include "flash.h"


MessageQueue *message;
Parameters *PARAM;

/* Private function prototypes -----------------------------------------------*/

uint16_t angleToHex(uint16_t angle);
void Packet_Handlers(uint8_t*);


/* MAIN ------------------------------------------------------------*/
int main(void)
{
  
  message = constructMessage();
  /* Initialize parameters by pulling from Flash */
  uint32_t *BAUD_RATE = 57600;
  uint32_t temp_read;
  Flash_Write_Data(BAUDRATE_ADDRESS, BAUD_RATE);
  volatile uint32_t *ptr = Flash_Read_Data(BAUDRATE_ADDRESS);
  volatile uint32_t value = ptr;
  PARAM = initializeParameters(5, 57600);

  /*** Initialization ***/
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
 	//DWT_Init();
	DRV8825_initStepper();
  AS5600_SetZero();
  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, 0);
  UART_DMA_Init();

  //DRV8825_setCurrentAngle(AS5600_GetCalAngle());
  volatile uint16_t angle;

  
  while(1){
    //transmit_buffer(array, sizeof(array));
    //HAL_Delay(5000);
    process_queue();
  }

}

// TODO: remove or replace function in appropriate place
uint16_t angleToHex(uint16_t angle){
  float factor = (4096.0/360.0);
  float conversion = (float)angle * factor; 
  return conversion;
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

