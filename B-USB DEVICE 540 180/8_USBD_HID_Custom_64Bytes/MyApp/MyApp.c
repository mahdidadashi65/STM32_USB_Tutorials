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
#include "usbd_customhid.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
uint8_t MyHID_Report[64];

uint8_t Counter=0;


extern UART_HandleTypeDef huart2;

int fputc(int ch , FILE *f)
{
	HAL_UART_Transmit(&huart2,(uint8_t*)&ch,1,0xffff);
	return ch;
}


union
{
	float _Float;
	uint8_t _U8[4];
}MyFtoB;

void Process_HID_Data_PC_To_MCU(uint8_t* data)
{
//	printf("New Data:");
//	for(int i=0;i<64;i++)
//	{
//		printf("%X ",data[i]);
//	}
//	printf("\r\n");
	
	if(data[0]==0x55)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,data[2]);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,data[3]);
		HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,data[4]);
		
		printf("Servo 8bit Data %d\r\n",data[5]);
		
		printf("32bit Data %X %X %X %X\r\n",data[6],data[7],data[8],data[9]);
		
		uint32_t My32bitData=data[6]+(data[7]<<8)+(data[8]<<16)+(data[9]<<24);
		
		printf("32bit Data2 %d\r\n",My32bitData);
		
		printf("32bit Data %X %X %X %X\r\n",data[10],data[11],data[12],data[13]);
		
		
		MyFtoB._U8[0]=data[10];
		MyFtoB._U8[1]=data[11];
		MyFtoB._U8[2]=data[12];
		MyFtoB._U8[3]=data[13];
		
		float MyFloatVal=MyFtoB._Float;
		printf("float Data %f\r\n",MyFloatVal);
		
	}
}


void MyApp(void)
{
	
	uint32_t MyINT32Val=2345678;
	
	float MyFloatVal=34.10;
	
	for(int i=0;i<64;i++)
	{
		MyHID_Report[i]=i;
	}
		
  while (1)
  {	  
	
	  MyHID_Report[0]=0xAA;
	  MyHID_Report[1]=!HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);
	  MyHID_Report[2]=!HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin);
	  MyHID_Report[3]=!HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin);
	  MyHID_Report[4]=!HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin);
	  MyHID_Report[5]=Counter;
	  Counter++;
	  
		MyHID_Report[6] = (uint8_t)(MyINT32Val         & 0xff);
		MyHID_Report[7] = (uint8_t)((MyINT32Val >> 8 ) & 0xff);
		MyHID_Report[8] = (uint8_t)((MyINT32Val >> 16) & 0xff);
		MyHID_Report[9] = (uint8_t)((MyINT32Val >> 24) & 0xff);
	  
	  MyINT32Val++;
	  
	  
	  
	  MyFtoB._Float=MyFloatVal;
	  MyHID_Report[10] =MyFtoB._U8[0];
	  MyHID_Report[11] =MyFtoB._U8[1];
	  MyHID_Report[12] =MyFtoB._U8[2];
	  MyHID_Report[13] =MyFtoB._U8[3];
	  
	  MyFloatVal+=0.5;
	  
	  
	  
	  

	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,MyHID_Report,64);
	HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
	HAL_Delay(100);
  }
}