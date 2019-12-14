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



#include "main.h"
#include "MyApp.h"

#include "usb_device.h"

typedef  void (*pFunction)(void);
pFunction JumpToApplication;
uint32_t JumpAddress;

void MyApp(void)
{
  if (HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 1)
  {
    /* Test if user code is programmed starting from USBD_DFU_APP_DEFAULT_ADD
     * address */
    if (((*(__IO uint32_t *) USBD_DFU_APP_DEFAULT_ADD) & 0x2FFC0000) ==
        0x20000000)
    {
      /* Jump to user application */
      JumpAddress = *(__IO uint32_t *) (USBD_DFU_APP_DEFAULT_ADD + 4);
      JumpToApplication = (pFunction) JumpAddress;

      /* Initialize user application's Stack Pointer */
      __set_MSP((*(__IO uint32_t *) USBD_DFU_APP_DEFAULT_ADD));
      JumpToApplication();
    }
  }
  
  HAL_Delay(200);
  MX_USB_DEVICE_Init();
  
  while (1)
  {
	  
	  HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	  HAL_Delay(100);
  }
	
}
