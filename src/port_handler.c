#include "port_handler.h"
#include "main.h"

/* Fields -------------------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern UART_HandleTypeDef huart1;
extern MessageQueue *message;
uint8_t temp_length;
uint8_t message_transferred;

/* Methods ------------------------------------------------------------------*/

/* @brief Initializes UART and DMA port with handle allowing for UART receive to have direct
 * memory access. Recevie uses idle line to trigger received event for variable message
 * lenght.
 * 
 * @param void
 * @return void
 */
void UART_DMA_Init(void) {
  rd_ptr = 0;
  
  HAL_UART_Receive_DMA(&huart1, rxBuffer, UART_RX__SZ);

  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);   // enable idle line interrupt  
  __HAL_DMA_ENABLE_IT (&hdma_usart1_rx, DMA_IT_TC);  // enable DMA Tx cplt interrupt
  __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT); // disable DMA half-transfer interrupt

  //HAL_UART_Receive_IT(&huart1, rxBuffer, UART_RX__SZ);
}

/* @brief Callback for UART RX idle line interrupt.
 * 
 * @param huart pointer to uart handle 
 * @return void
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  message_transferred = 0;
  UART_rx_transfer_to_queue();  
}

/* @brief Transfers UART receive buffer to queue to enable prompt 
 * rx_buffer readines for next message. Throws error if receive
 * idle event is thrown but buffer is empty.
 * 
 * @param void 
 * @return void
 */
void UART_rx_transfer_to_queue(void) {
  while(!rxBuffer_is_empty() && !isFull(message)) {
    enQueue(message, rxBuffer_Get());
    message_transferred = 1;
  }

// TODO: good 
  // if(!message_transferred){
  //   Error_Handler();
  // }

}

/* @brief Determines receive buffer is empty.
 * 
 * @param void
 * @return 1 if buffer is empty
 */
uint8_t rxBuffer_is_empty(void) {
  uint16_t dma_ptr = UART_DMA_WRITE_PTR;
	if(rd_ptr == dma_ptr) {
		return 1;
	}
	return 0;
}

/* @brief Grabs 1 byte of receive buffer.
 * 
 * @param void
 * @return 1 byte from receive buffer
 */
uint8_t rxBuffer_Get(void) {
	uint8_t message_byte = 0;
  uint16_t dma_ptr = UART_DMA_WRITE_PTR;
	if(rd_ptr != dma_ptr) {
		message_byte = rxBuffer[rd_ptr++];
		rd_ptr &= (UART_RX__SZ - 1);
	}
	return message_byte;
}

/* @brief Transmits message response with 2 millisecond timeout.
 * 
 * @param1 response[] message to send back to master
 * @param2 length message length
 * @return void *
 */
void transmit_buffer(uint8_t response[], uint16_t length){
  int i;
  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, HIGH);
  for (i=0; i<length; i++){
    txBuffer[i] = response[i];
  }
  /*  Fill rest of buffer with 0's*/
  for (i; i<UART_TX__SZ; i++){
    txBuffer[i] = 0;
  }
  HAL_UART_Transmit(&huart1, txBuffer, UART_TX__SZ, 2);
  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, LOW);
}
