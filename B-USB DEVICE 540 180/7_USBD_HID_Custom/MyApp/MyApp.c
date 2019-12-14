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
#include <string.h>
#include <stdio.h>


#include "usbd_customhid.h"
#include "usbd_custom_hid_if.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
extern UART_HandleTypeDef huart2;

int KeyPressCount=0;
GPIO_PinState KeyState[3];
int KeyState_Last[3]={0,0,0};

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART2 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

void Log(char* log)
{
   HAL_UART_Transmit(&huart2,(uint8_t*)log,strlen(log),100);	
}

void Test1(void)
{
	
	uint8_t MyReport[2];
	
	while(1)
	{
		KeyState[0] = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);	  
		if((KeyState[0] == GPIO_PIN_RESET) && (KeyState_Last[0]==0))
		{
			KeyState_Last[0]=1;
			KeyPressCount++;
			MyReport[0]=ADC_REPORT_ID;
			MyReport[1]=KeyPressCount;
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,MyReport,2);
		}	
		else if((KeyState[0] == GPIO_PIN_SET) && (KeyState_Last[0]==1))
		{
			KeyState_Last[0]=0;
		}	
	  
	  
		KeyState[1] = HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin);	  
		if((KeyState[1] == GPIO_PIN_RESET) && (KeyState_Last[1]==0))
		{
			KeyState_Last[1]=1;
			KeyPressCount--;
			MyReport[0]=ADC_REPORT_ID;
			MyReport[1]=KeyPressCount;
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,MyReport,2);
		}	
		else if((KeyState[1] == GPIO_PIN_SET) && (KeyState_Last[1]==1))
		{
			KeyState_Last[1]=0;
		} 
				
				
	    KeyState[2] = HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin);	  
		if((KeyState[2] == GPIO_PIN_RESET) && (KeyState_Last[2]==0))
		{
			KeyState_Last[2]=1;
		
			MyReport[0]=KEY_REPORT_ID;
			MyReport[1]=1;
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,MyReport,2);
		}	
		else if((KeyState[2] == GPIO_PIN_SET) && (KeyState_Last[2]==1))
		{
			KeyState_Last[2]=0;
			
			MyReport[0]=KEY_REPORT_ID;
			MyReport[1]=0;
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,MyReport,2);
		} 
		
	 
	  
	  HAL_Delay(10);
	}
}
void MyApp(void)
{	
	Log("USB HID Custom\r\n");
	

	Test1();
	
	while(1)
	{
			
	}
	
	
}
