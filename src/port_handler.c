#include "port_handler.h"

/* Fields -------------------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern UART_HandleTypeDef huart1;
extern MessageQueue *message;
uint8_t temp_length;

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
  
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);   // enable idle line interrupt    
  if (HAL_UART_Receive_DMA(&huart1, rxBuffer, UART_RX__SZ) != HAL_OK) {
    Error_Handler();
  }
  //__HAL_DMA_ENABLE_IT (&hdma_usart1_rx, DMA_IT_TC);  // enable DMA Tx cplt interrupt
  __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT); // disable DMA half-transfer interrupt
  HAL_UART_Receive_IT(&huart1, rxBuffer, UART_RX__SZ);
}

/* @brief Callback for UART RX idle line interrupt.
 * 
 * @param huart pointer to uart handle 
 * @return void
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(USART1 == huart1.Instance)                                   //Determine whether it is serial port 1
  {
      if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   //Judging whether it is idle interruption
      {
          __HAL_UART_CLEAR_IDLEFLAG(&huart1);                     //Clear idle interrupt sign (otherwise it will continue to enter interrupt)
          printf("\r\nUART1 Idle IQR Detected\r\n");
          USAR_UART_IDLECallback(huart);                          //Call interrupt handler
      }
  }
  //validate_header(get_header());
  // if () {
    
  // }
  // UART_rx_transfer_to_queue();  
}

//Declare external variables                                                 
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart)
{
  //Stop this DMA transmission
  HAL_UART_DMAStop(&huart1);  
                                                      
  //Calculate the length of the received data
  uint8_t data_length  = UART_RX__SZ - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);   
  
  //Zero Receiving Buffer
  memset(rxBuffer,0,data_length);                                            
  data_length = 0;
  
  //Restart to start DMA transmission of 255 bytes of data at a time
  HAL_UART_Receive_DMA(&huart1, (uint8_t*)rxBuffer, UART_RX__SZ);                    
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
  }
}

uint32_t* get_header(void) {
  int i;
  uint32_t header = 0;
  for (i=0; i<4; i++) {
    header += (get_one_byte_from_buffer() << i);
  }
  return header;
}

bool validate_header(uint32_t header) {
  bool flag = ((header & HEADER_MASK) == HEADER_MASK);
  return flag;
}

// void rx_filter(uint64_t) {

// }

/* @brief Determines receive buffer is empty.
 * 
 * @param void
 * @return true if buffer is empty
 */
bool rxBuffer_is_empty(void) {
  uint16_t dma_ptr = UART_DMA_WRITE_PTR;
	if(rd_ptr == dma_ptr) {
		return true;
	}
	return false;
}

/* @brief Grabs 1 byte of receive buffer.
 * 
 * @param void
 * @return 1 byte from receive buffer
 */
uint8_t get_one_byte_from_buffer(void) {
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
  // int i;
  // HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, HIGH);
  // for (i=0; i<length; i++){
  //   txBuffer[i] = response[i];
  // }
  // /*  Fill rest of buffer with 0's*/
  // for (i; i<UART_TX__SZ; i++){
  //   txBuffer[i] = 0;
  // }
  // HAL_UART_Transmit(&huart1, txBuffer, UART_TX__SZ, 2);
  // HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, LOW);
}
