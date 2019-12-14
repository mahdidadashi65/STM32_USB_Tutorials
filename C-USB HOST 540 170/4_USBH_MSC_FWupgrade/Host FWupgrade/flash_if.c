//           ****************************************************
//          **   Processor      : STM32F107VCT6                   **
//         ***   Frequency      : 8MHz ExtClock 72MHZ CPU Clock   ***
//        ****   AUTHOR         : Mahdi Dadashi                   ****
//       *****   STM32CubeMX    : V5.40                           *****
//      ******   STM32CubeF1    : V1.7.0                          ******
//       *****   Compiler       : KEIL uVision V5.26              *****
//        ****   Instagram      : instagram.com/mahdidadashi65/   ****
//         ***   Telegram       : t.me/mahdidadashi65/            ***
//          **   Github         : github.com/mahdidadashi65/      **
//           ****************************************************
//.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._
//.-''-._.-''-._.-''                                 ''-._.-''-._.-''-._.-''-._
//.-''-._.-''-._.-''      www.mahdidadashi.ir        ''-._.-''-._.-''-._.-''-._
//.-''-._.-''-._.-''                                 ''-._.-''-._.-''-._.-''-._
//.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._.-''-._



/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "MyAPP.h"
#include "flash_if.h"
//#include "stm32f1xx_hal_flash_ex.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t FirstSector = 0;
uint32_t NbOfSectors = 0;
uint32_t SectorError = 0;
uint32_t OB_RDP_LEVEL;

/* Private function prototypes -----------------------------------------------*/
//static uint32_t FLASH_If_GetSectorNumber(uint32_t Address);
static FLASH_OBProgramInitTypeDef FLASH_OBProgramInitStruct;
//static FLASH_EraseInitTypeDef FLASH_EraseInitStruct;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Unlocks the Flash to enable the flash control register access.
  * @param  None
  * @retval None
  */
void FLASH_If_FlashUnlock(void)
{
  HAL_FLASH_Unlock();
}

/**
  * @brief  Gets Flash readout protection status.
  * @param  None
  * @retval ReadOut protection status
  */
FlagStatus FLASH_If_ReadOutProtectionStatus(void)
{
  FlagStatus readoutstatus = RESET;

  FLASH_OBProgramInitStruct.RDPLevel = OB_RDP_LEVEL;

  HAL_FLASHEx_OBGetConfig(&FLASH_OBProgramInitStruct);

  if(OB_RDP_LEVEL == SET)
  {
    readoutstatus = SET;
  }
  else
  {
    readoutstatus = RESET;
  }

  return readoutstatus;
}

/**
  * @brief  Erases the required FLASH Sectors.
  * @param  Address: Start address for erasing data
  * @retval 0: Erase sectors done with success
  *         1: Erase error
  */
uint32_t FLASH_If_EraseSectors(uint32_t Address)
{
  /* Erase the user Flash area
    (area defined by APPLICATION_ADDRESS and USER_FLASH_LAST_PAGE_ADDRESS) ****/

  if(Address <= (uint32_t) USER_FLASH_LAST_PAGE_ADDRESS)
  {
//    /* Get the 1st sector to erase */
//    FirstSector = FLASH_If_GetSectorNumber(Address);
//    /* Get the number of sector to erase from 1st sector */
//    NbOfSectors = FLASH_If_GetSectorNumber(USER_FLASH_LAST_PAGE_ADDRESS) - FirstSector + 1;
//    FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
//    FLASH_EraseInitStruct.Sector = FirstSector;
//    FLASH_EraseInitStruct.NbSectors = NbOfSectors;
//    FLASH_EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;

//    if(HAL_FLASHEx_Erase(&FLASH_EraseInitStruct, &SectorError) != HAL_OK)
//      return (1);
	  
  uint32_t NbOfPages = 0;
  uint32_t PageError = 0;
  /* Variable contains Flash operation status */
  HAL_StatusTypeDef status;
  FLASH_EraseInitTypeDef FLASH_EraseInitStruct;

  /* Get the number of sector to erase from 1st sector */
  NbOfPages =((USER_FLASH_LAST_PAGE_ADDRESS - APPLICATION_ADDRESS) / FLASH_PAGE_SIZE) + 1;
	
  FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
  FLASH_EraseInitStruct.PageAddress = APPLICATION_ADDRESS;
  FLASH_EraseInitStruct.NbPages = NbOfPages;
  status = HAL_FLASHEx_Erase(&FLASH_EraseInitStruct, &PageError);

  if (status != HAL_OK)
  {
    return 1;
  }
  
  }
  else
  {
    return (1);
  }

  return (0);
}

/**
  * @brief  Writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  Address: Start address for writing data buffer
  * @param  Data: Pointer on data buffer
  * @retval 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  */
uint32_t FLASH_If_Write(uint32_t Address, uint32_t Data)
{
  /* Program the user Flash area word by word
    (area defined by FLASH_USER_START_ADDR and APPLICATION_ADDRESS) ***********/

  if(Address <= (uint32_t) USER_FLASH_LAST_PAGE_ADDRESS)
  {
    if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data)!= HAL_OK)
      return (1);
  }
  else
  {
    return (1);
  }

  return (0);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
