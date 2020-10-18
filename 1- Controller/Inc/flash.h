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
 * that write to Pages 117-127 ( (0x0801FC00 - 0x1FFF7FF).
 * Each address hold uint32_t data so increments by
 * 4 bytes between addresses or 0x20.
 */
// TODO: Determine Addresses
#define MODEL_NUMBER_ADDRESS 0x0801FC00 
#define MODEL_INFORMATION_ADDRESS 0x10801FBFF 

#define FIRMWARE_VERSION_ADDRESS 0x0801FC40
#define ID_ADDRESS 

#define BAUD_RATE_ADDRESS 
#define RETURN_DELAY_TIME_ADDRESS 

#define DRIVE_MODE_ADDRESS 
#define OPERATING_MODE_ADDRESS 

#define SECONDARY_ID_ADDRESS 
#define PROTOCOL_TYPE_ADDRESS 

#define HOMING_OFFSET_ADDRESS 
#define MOVING_THRESHOLD_ADDRESS

#define TEMPERATURE_LIMIT_ADDRESS 
#define MAX_VOLTAGE_LIMIT_ADDRESS 

#define MIN_VOLTAGE_LIMIT_ADDRESS 
#define PWM_LIMIT_ADDRESS 

#define VELOCITY_LIMIT_ADDRESS 
#define MAX_POSITION_LIMIT_ADDRESS 

#define MIN_POSITION_LIMIT_ADDRESS 
#define SHUTDOWN_ADDRESS 

void Flash_Write_Data (uint32_t StartPageAddress, uint32_t DATA_32);
uint32_t* Flash_Read_Data (uint32_t StartPageAddress);
void Convert_To_Str (uint32_t *data, char *str);



/********************  FLASH_Error_Codes   ***********************//*
HAL_FLASH_ERROR_NONE      0x00U  // No error
HAL_FLASH_ERROR_PROG      0x01U  // Programming error
HAL_FLASH_ERROR_WRP       0x02U  // Write protection error
HAL_FLASH_ERROR_OPTV      0x04U  // Option validity error
*/


#endif /* INC_FLASH_PAGE_H_ */
