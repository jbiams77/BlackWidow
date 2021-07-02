
/*System Includes ------------------------------------------------------------------*/

#include "stm32f1xx_hal.h"

/*Project Includes ------------------------------------------------------------------*/
#include "utility.h"
#include "fifo.h"
#include "dwt_delay.h"
#include "port_handler.h"

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
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
  //HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, 0);
  UART_DMA_Init();
  //initialize_stored_parameters();

  while(1) {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    HAL_Delay(500);
  }
}


