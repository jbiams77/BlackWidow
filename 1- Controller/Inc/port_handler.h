#include <stdint.h>
#include <stdlib.h>
#include "queue.h"

#ifndef __PORT_HANDLER_H_
#define __PORT_HANDLER_H_

#define UART_RX_RINGBUFF_SZ 512
#define UART_RX_MAX_MESSAGE_LEN 256
#define UART_DMA_WRITE_PTR ((UART_RX_RINGBUFF_SZ - huart1.hdmarx->Instance->CNDTR) & (UART_RX_RINGBUFF_SZ - 1)) 

uint8_t rxBuf[UART_RX_RINGBUFF_SZ];
uint8_t processBuf[UART_RX_RINGBUFF_SZ];
uint8_t rxLen;
uint16_t rxLastPos, rxThisPos;

#endif