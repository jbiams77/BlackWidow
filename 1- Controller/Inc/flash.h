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
 * Each address hold uint32_t data so increments by
 * 4 bytes between addresses.
 */
#define MODEL_NUMBER_ADDRESS        0x0801FC00 
#define MODEL_INFORMATION_ADDRESS   0x0801FC04
#define FIRMWARE_VERSION_ADDRESS    0x0801FC08
#define ID_ADDRESS                  0x0801FC0C
#define BAUD_RATE_ADDRESS           0x0801FC10
#define RETURN_DELAY_TIME_ADDRESS   0x0801FC14
#define DRIVE_MODE_ADDRESS          0x0801FC18
#define OPERATING_MODE_ADDRESS      0x0801FC1C
#define SECONDARY_ID_ADDRESS        0x0801FC20
#define PROTOCOL_TYPE_ADDRESS       0x0801FC24
#define HOMING_OFFSET_ADDRESS       0x0801FC28
#define MOVING_THRESHOLD_ADDRESS    0x0801FC2C
#define TEMPERATURE_LIMIT_ADDRESS   0x0801FC30
#define MAX_VOLTAGE_LIMIT_ADDRESS   0x0801FC34
#define MIN_VOLTAGE_LIMIT_ADDRESS   0x0801FC38
#define PWM_LIMIT_ADDRESS           0x0801FC3C
#define VELOCITY_LIMIT_ADDRESS      0x0801FC40
#define MAX_POSITION_LIMIT_ADDRESS  0x0801FC44
#define MIN_POSITION_LIMIT_ADDRESS  0x0801FC48
#define SHUTDOWN_ADDRESS            0x0801FC4C

void Flash_Write_Data (uint32_t StartPageAddress, uint32_t DATA_32);
uint32_t* Flash_Read_Data (uint32_t StartPageAddress);



#endif /* INC_FLASH_PAGE_H_ */
