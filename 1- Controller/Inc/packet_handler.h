#include <stdint.h>
#include <stdlib.h>
#include "queue.h"

#ifndef __PACKET_HANDLER_H_
#define __PACKET_HANDLER_H_

#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET

#define BUFFER_SIZE 8
#define HEADER1 0
#define HEADER2 1
#define HEADER3 2
#define RSRVD 3
#define PACKET_ID  4
#define LENGTH_LOW 5
#define LENGTH_HIGH 6

#define PING 1
#define READ 2
#define WRITE 3
#define REG_WRITE 4
#define ACTION 5
#define FACTORY_RESET 6
#define REBOOT 8
#define CLEAR 10
#define STATUS 55
#define SYNC_READ 82
#define SYNC_WRITE 83
#define BULK_READ 92
#define BULK_WRITE 93


/*------FIELDS----------------------------------------*/
extern MessageQueue *message;
uint8_t instruction;
uint8_t param[20];
uint8_t crc[2];
extern Parameters *PARAM;

/*------FUNCTION PROTOTYPES---------------------------*/
void process_queue(void);
void process_message(uint16_t );
void ping(void);
void read(void); 
void write(void); 
void reg_write(void); 
void action(void); 
void factory_reset(void);
void reboot(void); 
void clear(void); 
void status(void); 
void sync_read(void); 
void sync_write(void); 
void bulk_read(void); 
void bulk_write(void); 

#endif