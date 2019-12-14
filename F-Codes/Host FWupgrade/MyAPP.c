//           ****************************************************
//          **   Processor      : STM32F107VCT6                   **
//         ***   Frequency      : 8MHz ExtClock 72MHZ CPU Clock   ***
//        ****   AUTHOR         : Mahdi Dadashi                   ****
//       *****   STM32CubeMX    : V5.40                           *****
//      ******   STM32CubeF1    : V1.8.0                          ******
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




#include "MyApp.h"
#include "main.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "FatFS.h"
#include "usb_host.h"
#include "flash_if.h"

       
/* This value can be equal to (512 * x) according to RAM size availability with x=[1, 128]*/
#define BUFFER_SIZE        ((uint16_t)512*4)

uint32_t JumpAddress;
pFunction Jump_To_Application;

static uint32_t TmpReadSize = 0x00;
static uint32_t RamAddress = 0x00;
static __IO uint32_t LastPGAddress = APPLICATION_ADDRESS;
static uint8_t RAM_Buf[BUFFER_SIZE] = { 0x00 };
extern ApplicationTypeDef Appli_state;
extern void COMMAND_ProgramFlashMemory(void);


FIL MyFileR;                  
extern DIR dir;
extern FILINFO fno;


char DOWNLOAD_FILENAME[20]; 


extern UART_HandleTypeDef huart2;

int fputc( int ch, FILE *f )
{
    HAL_UART_Transmit(&huart2, ( uint8_t * )&ch, 1, 0xFFFF );
    return ch;
}


void Fail_Handler(void)
{
	printf("Fail_Handler\r\n");
  while (1)
  {
    /* Toggle LED3 */
	HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
    HAL_Delay(100);
  }
}


void Erase_Fail_Handler(void)
{
	printf("Erase_Fail_Handler\r\n");
  while (1)
  {
    /* Toggle LED2 and LED3 */
     HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
    HAL_Delay(100);
  }
}


void FatFs_Fail_Handler(void)
{
	printf("FatFs_Fail_Handler\r\n");
  while (1)
  {
    /* Toggle LED3 and LED4 */
    HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);	  
    HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
    HAL_Delay(100);
  }
}


void COMMAND_Download(void)
{
  /* Open the binary file to be downloaded */
	int res=f_open(&MyFileR, DOWNLOAD_FILENAME, FA_READ);
	if( res== FR_OK)
	{
		if(f_size(&MyFileR) > USER_FLASH_SIZE)
		{
		  /* No available Flash memory size for the binary file: Turn LED4 On and
			 Toggle LED3 in infinite loop */
		  HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);
		  Fail_Handler();
		}
		else
		{
			printf("f_size:%d\r\n",(int)f_size(&MyFileR));
		  /* Download On Going: Turn LED4 On */
		  HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);

		  /* Erase FLASH sectors to download image */
		  if(FLASH_If_EraseSectors(APPLICATION_ADDRESS) != 0x00)
		  {
			/* Flash erase error: Turn LED4 On and Toggle LED2 and LED3 in
			   infinite loop */
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_RESET);
			Erase_Fail_Handler();
		  }

		  /* Program flash memory */
		  COMMAND_ProgramFlashMemory();

		  /* Download Done: Turn LED4 Off and LED2 On */
		  HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);

		  /* Close file */
		  f_close(&MyFileR);
		}
	}
	else
	{
		printf("Err:%d\r\n",res);
		/* The binary file is not available: Turn LED1, LED2 and LED4 On and Toggle
		   LED3 in infinite loop */
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);
		Fail_Handler();

	}
}


void COMMAND_Jump(void)
{
  /* Software reset */
  NVIC_SystemReset();
}


void COMMAND_ProgramFlashMemory(void)
{
  uint32_t programcounter = 0x00;
  uint8_t readflag = TRUE;
  uint16_t bytesread;

  /* RAM Address Initialization */
  RamAddress = (uint32_t) &RAM_Buf;

  /* Erase address init */
  LastPGAddress = APPLICATION_ADDRESS;

  /* While file still contain data */
  while ((readflag == TRUE))
  {
    /* Read maximum 512 Kbyte from the selected file */
    f_read (&MyFileR, RAM_Buf, BUFFER_SIZE, (void *)&bytesread);

    /* Temp variable */
    TmpReadSize = bytesread;

    /* The read data < "BUFFER_SIZE" Kbyte */
    if(TmpReadSize < BUFFER_SIZE)
    {
      readflag = FALSE;
    }

    /* Program flash memory */
    for (programcounter = 0; programcounter < TmpReadSize; programcounter += 4)
    {
		//printf("FLASH_If_Write 1:%d\r\n",programcounter);
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
      /* Write word into flash memory */
      if (FLASH_If_Write((LastPGAddress + programcounter),
                         *(uint32_t *) (RamAddress + programcounter)) != 0x00)
      {
        /* Flash programming error: Turn LED2 On and Toggle LED3 in infinite
         * loop */
        HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
        Fail_Handler();
      }
	  //printf("FLASH_If_Write 2:%d\r\n",programcounter);		
      HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
    }
    /* Update last programmed address value */
    LastPGAddress += TmpReadSize;
  }
}

void FW_UPGRADE_Process(void)
{
	if(Appli_state == APPLICATION_READY)
	{
      HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);		
      HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
      COMMAND_Download();
      COMMAND_Jump();
    }
	else
	{
		/* Toggle LED3: USB device disconnected */
		HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
		HAL_Delay(100);
	}
}

 void MyApp_USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{
	printf("User:%d\r\n",id);
  switch (id)
  {
  case HOST_USER_SELECT_CONFIGURATION:
    break;

  case HOST_USER_DISCONNECTION:
    Appli_state = APPLICATION_DISCONNECT;
    if (f_mount(NULL, USBHPath, 0) != FR_OK)
    {
      FatFs_Fail_Handler();
    }
    if (FATFS_UnLinkDriver(USBHPath) != 0)
    {
      FatFs_Fail_Handler();
    }
    break;

  case HOST_USER_CLASS_ACTIVE:
    Appli_state = APPLICATION_READY;
  
      if (f_mount(&USBHFatFS, USBHPath, 0) != FR_OK)
      {
        FatFs_Fail_Handler();
      }
	  
    break;

  case HOST_USER_CONNECTION:
    Appli_state = APPLICATION_START;
    break;

  default:
    break;
  }
}

void MyApp_RunLastApp(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED4_Pin|LED3_Pin|LED2_Pin|LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED4_Pin LED3_Pin LED2_Pin LED1_Pin */
  GPIO_InitStruct.Pin = LED4_Pin|LED3_Pin|LED2_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SW_UP_Pin SW_DOWN_Pin SW_LEFT_Pin SW_RIGHT_Pin */
  GPIO_InitStruct.Pin = KEY1_Pin|KEY2_Pin|KEY3_Pin|KEY4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  
  FLASH_If_FlashUnlock();

  if (HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == GPIO_PIN_RESET)
  {
	  sprintf(DOWNLOAD_FILENAME,"%s%s",USBHPath,"image1.bin"); 
  }
  else if (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET)
  {
	  sprintf(DOWNLOAD_FILENAME,"%s%s",USBHPath,"image2.bin"); 
  }
  else
  {
    /* Check Vector Table: Test if user code is programmed starting from address
    "APPLICATION_ADDRESS" */
    if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0xFF000000 ) == 0x20000000)
    {
      /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
      Jump_To_Application();
    }
  }

}
void MyApp_RunBootLoader(void)
{
	while (1)
	{
	 MX_USB_HOST_Process();
	 FW_UPGRADE_Process();
	}

}