/*
 * FLASH_PAGE.h
 *
 *  Created on: 08-May-2020
 *      Author: controllerstech
 */

#ifndef __FLASH_H_
#define __FLASH_H_

#include "stm32f1xx_hal.h"

/* Black Widow EEPROM writable settings address
 * that write to Page 127( (0x0801FC00 - 0x1FFF7FF).
 * Each address hold uint8_t data so increments by
 * 1 byte between addresses.
 */
#define MODEL_NUMBER_ADDRESS        0x0801FC00 
#define MODEL_INFORMATION_ADDRESS   0x0801FC01
#define FIRMWARE_VERSION_ADDRESS    0x0801FC02
#define ID_ADDRESS                  0x0801FC03
#define BAUD_RATE_ADDRESS           0x0801FC04
#define RETURN_DELAY_TIME_ADDRESS   0x0801FC05
#define DRIVE_MODE_ADDRESS          0x0801FC06
#define OPERATING_MODE_ADDRESS      0x0801FC07
#define SECONDARY_ID_ADDRESS        0x0801FC08
#define PROTOCOL_TYPE_ADDRESS       0x0801FC09
#define HOMING_OFFSET_ADDRESS       0x0801FC0A
#define MOVING_THRESHOLD_ADDRESS    0x0801FC0B
#define TEMPERATURE_LIMIT_ADDRESS   0x0801FC0C
#define MAX_VOLTAGE_LIMIT_ADDRESS   0x0801FC0D
#define MIN_VOLTAGE_LIMIT_ADDRESS   0x0801FC0E
#define PWM_LIMIT_ADDRESS           0x0801FC0F
#define VELOCITY_LIMIT_ADDRESS      0x0801FC10
#define MAX_POSITION_LIMIT_ADDRESS  0x0801FC11
#define MIN_POSITION_LIMIT_ADDRESS  0x0801FC12
#define SHUTDOWN_ADDRESS            0x0801FC13

void Flash_Write_Data (uint32_t StartPageAddress, uint8_t DATA_32);
uint8_t* Flash_Read(uint32_t StartPageAddress);



#endif 
