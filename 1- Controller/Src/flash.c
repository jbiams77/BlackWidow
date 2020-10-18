
#include "flash.h"
#include "string.h"
#include "stdio.h"


void Flash_Write(uint32_t StartPageAddress, uint32_t DATA_32)
{

	/* Unlock the Flash to enable the flash control register access *************/
	HAL_FLASH_Unlock();
	
	// TODO: catch falsh write error in if statement
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartPageAddress, DATA_32); //== HAL_OK));
	//    }

	/* Lock the Flash to disable the flash control register access (recommended
	   to protect the FLASH memory against possible unwanted operation) *********/
	HAL_FLASH_Lock();

}


uint32_t* Flash_Read_Data (uint32_t StartPageAddress)
{

	return *(__IO uint32_t *)StartPageAddress;

}

