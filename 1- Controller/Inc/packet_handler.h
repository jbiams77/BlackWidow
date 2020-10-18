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

// Dynamixel Communication 2.0 writable settings
#define MODEL_NUMBER 0
#define MODEL_INFORMATION 2
#define FIRMWARE_VERSION 6
#define ID 7
#define BAUD_RATE 8
#define RETURN_DELAY_TIME 9
#define DRIVE_MODE 10 
#define OPERATING_MODE 11 
#define SECONDARY_ID 12
#define PROTOCOL_TYPE 13 
#define HOMING_OFFSET 20 
#define MOVING_THRESHOLD 24 
#define TEMPERATURE_LIMIT 31 
#define MAX_VOLTAGE_LIMIT 32
#define MIN_VOLTAGE_LIMIT 34
#define PWM_LIMIT 36 
#define VELOCITY_LIMIT 44
#define MAX_POSITION_LIMIT 48
#define MIN_POSITION_LIMIT 52
#define SHUTDOWN 63



/*------FUNCTION PROTOTYPES---------------------------*/
void process_queue(void);
void process_message(void);
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