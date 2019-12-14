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


extern USBD_HandleTypeDef hUsbDeviceFS;

void Test1_Mouse(void)
{
		int8_t Report[4]={0,2,2,0};
	//Report[0]==buttons
	//Report[1]==x
	//Report[2]==y
	//Report[3]==wheel
	while(1)
	{
		USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)Report,4);
		HAL_Delay(300);
	}
}


struct HIDmouseReport_t
{
	uint8_t buttons;
	int8_t x;
	int8_t y;
	int8_t wheel;
};

struct HIDmouseReport_t HIDmouseReport;

void Test2_Mouse(void)
{
	HIDmouseReport.buttons=0;
	HIDmouseReport.x=-5;
	HIDmouseReport.y=0;
	HIDmouseReport.wheel=0;
	while(1)
	{
		USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&HIDmouseReport,4);
		HAL_Delay(300);
	}
}

void Test3_Mouse(void)
{
	while (1)
	{
	    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
		{
			HIDmouseReport.y = -5;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.y = 0;
		}
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
		{
			HIDmouseReport.y = 5;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.y = 0;
		}
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
        {
			HIDmouseReport.x = 5;			
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.x = 0;
		}
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
		{	
			HIDmouseReport.x =-5;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.x = 0;
		}

		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(50);
	}
}


void Test4_Mouse(void)
{
	while (1)
	{
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
		{
			HIDmouseReport.y = -5;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.y = 0;
		}
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
		{
			HIDmouseReport.y = 5;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.y = 0;
		}

		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
        {
			HIDmouseReport.buttons = 2;//Right
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HAL_Delay(5);			
			HIDmouseReport.buttons = 0;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
		}
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
		{	
			HIDmouseReport.buttons = 1;//Left
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HAL_Delay(5);			
			HIDmouseReport.buttons = 0;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
		}
		
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		HAL_Delay(50);
	}
}


void Test5_Mouse(void)
{
	while (1)
	{
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
		{
			HIDmouseReport.wheel = 1;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.wheel = 0;
		}		
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
		{
			HIDmouseReport.wheel = -1;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.wheel = 0;
		}
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
        {
			HIDmouseReport.x = 5;			
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.x = 0;
		}
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
		{	
			HIDmouseReport.x =-5;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDmouseReport, sizeof(struct HIDmouseReport_t));
			HIDmouseReport.x = 0;
		}
  	  
		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		HAL_Delay(50);
	}
}




void MyApp(void)
{
	//Test1_Mouse();
	//Test2_Mouse();
	Test3_Mouse();
	//Test4_Mouse();
	//Test5_Mouse();
}