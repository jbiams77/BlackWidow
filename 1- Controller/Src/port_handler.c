#include "port_handler.h"
#include "main.h"

extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;
extern MessageQueue *message;
uint8_t temp_length;

/* UART Managemnt ------------------------------------------------------------*/


void UART_DMA_Init(void) {
  rd_ptr = 0;
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);   // enable idle line interrupt  
  HAL_UART_Receive_DMA(&huart1, rxBuffer, UART_RX__SZ);
}


void transmit_buffer(uint8_t response[], uint16_t length){
  // transmit reply here
}

void UART_RxComplete(void) {
  while(!rxBuffer_is_empty() && !isFull(message)){
    enQueue(message, rxBuffer_Get());
  }
  volatile int x = 1;
}

uint8_t rxBuffer_is_empty(void) {
  uint16_t dma_ptr = UART_DMA_WRITE_PTR;
	if(rd_ptr == dma_ptr) {
		return 1;
	}
	return 0;
}

uint8_t rxBuffer_Get(void) {
	uint8_t c = 0;
  uint16_t dma_ptr = UART_DMA_WRITE_PTR;
	if(rd_ptr != dma_ptr) {
		c = rxBuffer[rd_ptr++];
		rd_ptr &= (UART_RX__SZ - 1);
	}
	return c;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  UART_RxComplete();
}

