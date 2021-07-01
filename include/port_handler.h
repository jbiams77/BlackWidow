#include <stdint.h>
#include <stdlib.h>
#include "queue.h"

#ifndef __PORT_HANDLER_H_
#define __PORT_HANDLER_H_

#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET

#define UART_RX__SZ 64
#define UART_TX__SZ 64
#define UART_DMA_WRITE_PTR ((UART_RX__SZ - huart1.hdmarx->Instance->CNDTR) & (UART_RX__SZ - 1)) 

uint8_t rxBuffer[UART_RX__SZ];
uint8_t txBuffer[UART_TX__SZ];
uint8_t rd_ptr;

void UART_DMA_Init(void);
void transmit_buffer(uint8_t [], uint16_t );
void UART_RxComplete(void);
uint8_t rxBuffer_is_empty(void);
uint8_t rxBuffer_Get(void);

#endif