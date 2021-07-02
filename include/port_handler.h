#pragma once

#include "utility.h"
#include "stm32f1xx_hal.h"
#include "fifo.h"

uint8_t rxBuffer[UART_RX__SZ];
uint8_t txBuffer[UART_TX__SZ];
uint8_t rd_ptr;

void UART_DMA_Init(void);
void transmit_buffer(uint8_t [], uint16_t );
void UART_RxComplete(void);
void UART_DMA_Init(void);
void UART_rx_transfer_to_queue(void);
uint8_t rxBuffer_is_empty(void);
uint8_t get_one_byte_from_buffer(void);
uint32_t* get_header(void);
bool validate_header(uint32_t header);
