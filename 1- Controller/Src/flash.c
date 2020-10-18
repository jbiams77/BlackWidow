/*
 * FlASH_PAGE.c
 *
 *  Created on: 08-May-2020
 *      Author: controllerstech
 */

#include "flash.h"
#include "string.h"
#include "stdio.h"

static uint32_t GetPage(uint32_t Address)
{
  for (int indx=0; indx<128; indx++)
  {
	  if((Address < (0x08000000 + (1024 *(indx+1))) ) && (Address >= (0x08000000 + 1024*indx)))
	  {
		  return (0x08000000 + 1024*indx);
	  }
  }

  return -1;
}

void Flash_Write_Data (uint32_t StartPageAddress, uint32_t DATA_32)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError;
	int sofar=0;

	// int numberofwords = (strlen(DATA_32)/4) + ((strlen(DATA_32) % 4) != 0);

	  /* Unlock the Flash to enable the flash control register access *************/
	   HAL_FLASH_Unlock();

	   /* Erase the user Flash area*/

	  uint32_t StartPage = GetPage(StartPageAddress);
	  //uint32_t EndPageAdress = StartPageAddress + numberofwords*4;
	  //uint32_t EndPage = GetPage(EndPageAdress);

	   /* Fill EraseInit structure*/
	   EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	   EraseInitStruct.PageAddress = StartPage;
	   //EraseInitStruct.NbPages     = ((EndPage - StartPage)/FLASH_PAGE_SIZE) +1;

	//    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
	//    {
	//      /*Error occurred while page erase.*/
	// 		Error_Handler();
	//    }

	   /* Program the user Flash area word by word*/

	//    while (sofar<numberofwords)
	//    {
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

void Convert_To_Str (uint32_t *data, char *str)
{
	int numberofbytes = ((strlen(data)/4) + ((strlen(data) % 4) != 0)) *4;

	for (int i=0; i<numberofbytes; i++)
	{
		str[i] = data[i/4]>>(8*(i%4));
	}
}

