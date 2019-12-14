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
#include "usb_device.h"
#include "usbd_hid.h"

#include "hid_keyboard.h"



extern USBD_HandleTypeDef hUsbDeviceFS;

void Test1_KeyBorad(void)
{
		int8_t Report[5]={1,0,0x10,0,0};
	//Report[0]== id == 1
	//Report[1]== modifiers == 0
	//Report[2]== Key1  0x10=='m'
	//Report[3]== Key2
	//Report[4]== Key3
	while(1)
	{
		Report[2]=0x10;
		USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)Report,5);
		HAL_Delay(30);
		
		Report[2]=0;
		USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)Report,5);
		HAL_Delay(3000);
		
	}
}


struct HIDkeyboardReport_t
{
	uint8_t id;
	uint8_t modifiers;
	uint8_t key1;
	uint8_t key2;
	uint8_t key3;
};

struct HIDkeyboardReport_t HIDkeyboardReport;

void Test2_KeyBoard(void)
{
	HIDkeyboardReport.id=1;
	HIDkeyboardReport.modifiers=0;
	
	while(1)
	{
		HIDkeyboardReport.key1=0x20;
		USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDkeyboardReport,5);
		HAL_Delay(30);
		
		HIDkeyboardReport.key1=0;
		USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDkeyboardReport,5);
		HAL_Delay(3000);
	}
}

void Test3_KeyBoard(void)
{
	
	HIDkeyboardReport.id=1;
	while (1)
	{
	    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
		{
			HIDkeyboardReport.key1=KB_X;
			HIDkeyboardReport.modifiers=USB_HID_MODIFIER_NONE;
			USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDkeyboardReport,5);
			HAL_Delay(30);
			HIDkeyboardReport.key1=KB_NONE;
			HIDkeyboardReport.modifiers=USB_HID_MODIFIER_NONE;
			USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDkeyboardReport,5);
			HAL_Delay(30);
		}
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
		{
			HIDkeyboardReport.key1=KB_X;
			HIDkeyboardReport.modifiers=USB_HID_MODIFIER_LEFT_SHIFT;
			USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDkeyboardReport,5);
			HAL_Delay(30);

			HIDkeyboardReport.key1=KB_NONE;
			HIDkeyboardReport.modifiers=USB_HID_MODIFIER_NONE;
			USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDkeyboardReport,5);
			HAL_Delay(30);
		}		
		HAL_Delay(100);
	}
}

void Test4_KeyBoard(void)
{
	char* Text1="Hello My Keyboard\r\n";
	HIDkeyboardReport.id=1;
	while (1)
	{
	    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
		{
			SendKeyBoardChar('A');
		}
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
		{
			SendKeyBoardChar('*');
		}
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
		{
			for(int i=0;i<strlen(Text1);i++)
			{						
				SendKeyBoardChar(Text1[i]);
			}
		}		
		HAL_Delay(100);
	}
}



struct HIDmediaReport_t
{
	uint8_t id;
	uint8_t key;

};
struct HIDmediaReport_t HIDmediaReport;

void Test5_KeyBoard(void)
{
	HIDmediaReport.id=2;
	while (1)
	{
	    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
		{
			HIDmediaReport.key=USB_HID_VOL_UP;
			USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDmediaReport,2);
			HAL_Delay(30);
			HIDmediaReport.key=0;
			USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDmediaReport,2);
			HAL_Delay(30);
		}
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
		{
			HIDmediaReport.key=USB_HID_VOL_DEC;
			USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDmediaReport,2);
			HAL_Delay(30);
			HIDmediaReport.key=0;
			USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDmediaReport,2);
			HAL_Delay(30);
		}
		
		HAL_Delay(100);
	}
}



void MyApp(void)
{
	//Test1_KeyBorad();
	//Test2_KeyBoard();
	//Test3_KeyBoard();
	Test5_KeyBoard();
}