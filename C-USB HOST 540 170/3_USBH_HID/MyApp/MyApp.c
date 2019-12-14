
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



#include "main.h"
#include "MyApp.h"
#include <string.h>
#include <stdio.h>

#include "usb_host.h"
#include "usbh_hid.h"


extern UART_HandleTypeDef huart2;


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


void USBH_HID_EventCallback(USBH_HandleTypeDef *phost)
{
	HID_TypeTypeDef MyHIDType;
	MyHIDType=USBH_HID_GetDeviceType(phost);
	
	if(MyHIDType==HID_MOUSE)
	{
		HID_MOUSE_Info_TypeDef *MyMouse_info;
		MyMouse_info=USBH_HID_GetMouseInfo(phost);
		printf("MouseInfo:X:%d Y:%d BTN: %d %d %d\r\n",MyMouse_info->x,MyMouse_info->y,MyMouse_info->buttons[0],MyMouse_info->buttons[1],MyMouse_info->buttons[2]);
	}
	else if(MyHIDType==HID_KEYBOARD)
	{
		HID_KEYBD_Info_TypeDef *keyboard_info;
		char ascii;
			
		keyboard_info = USBH_HID_GetKeybdInfo(phost);

		if( keyboard_info != NULL )
		{
			ascii = USBH_HID_GetASCIICode(keyboard_info);
			if( ascii != 0 )
			{
				printf("%c",ascii);
			}
			printf("keys[6] %x %x %x %x %x %x ",keyboard_info->keys[0],\
						keyboard_info->keys[1],\
						keyboard_info->keys[2],\
						keyboard_info->keys[3],\
						keyboard_info->keys[4],\
						keyboard_info->keys[5]);
			}
		}

	

}


void MyApp(void)
{	
	printf("Test_USBH_HID\r\n");
	
	while(1)
	{
		
		MX_USB_HOST_Process();
		//HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		//HAL_Delay(50);
					
	}
	
	
}
