#include "port_handler.h"
#include "main.h"

extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;
extern MessageQueue *message;

/* UART Managemnt ------------------------------------------------------------*/


void UARTRXInit(void) {
  rxLastPos=0;
  rxThisPos=0; 
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);   // enable idle line interrupt
  //hdma_uart1_rx.Instance->CR &= ~DMA_SxCR_HTIE;  // disable uart half tx interrupt
  HAL_UART_Receive_DMA(&huart1,rxBuf,UART_RX_RINGBUFF_SZ); 
}

void UARTRxComplete(void) {
  uint8_t addr;
  uint16_t len;
  rxThisPos = UART_DMA_WRITE_PTR; //get current write pointer
  len=(rxThisPos-rxLastPos+UART_RX_RINGBUFF_SZ)%UART_RX_RINGBUFF_SZ; //calculate how far the DMA write pointer has moved
  int i;
  for (i=rxLastPos; i<(rxThisPos+len);i++){
    enQueue(message, rxBuf[i]);
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1) {       
    if (__HAL_UART_GET_FLAG (&huart1, UART_FLAG_IDLE)) {
      UARTRxComplete();
    }
  }
}