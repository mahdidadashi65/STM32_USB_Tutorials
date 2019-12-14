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

#include "usbd_cdc_if.h"


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

void Log(char* log)
{
   //HAL_UART_Transmit(&huart2,(uint8_t*)log,strlen(log),100);
   CDC_Transmit_FS((uint8_t*)log,strlen(log));	
}


////////////////////////////////////////
uint8_t RXBuffer[40];
uint8_t RXBufferCount=0;
uint8_t NewDataInt;
uint8_t NewDataLineCount=0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART2)
	{
		RXBuffer[RXBufferCount++]=NewDataInt;
		RXBuffer[RXBufferCount]=0;
		if((NewDataInt=='\n')&&(RXBufferCount>0))
		{
			NewDataLineCount=RXBufferCount;
			RXBufferCount=0;
		}
		
		HAL_UART_Receive_IT(&huart2,&NewDataInt,1);
	}	
}


int BlinkTime=200;
void Process_UART_Data(uint8_t* Data)
{	
	if(strstr((char*)Data,"LED1:1")!=0)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_SET);
	}
	if(strstr((char*)Data,"LED1:0")!=0)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_RESET);
	}
	if(strstr((char*)Data,"LED2:1")!=0)
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_SET);
	}
	if(strstr((char*)Data,"LED2:0")!=0)
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_RESET);
	}
	if(strstr((char*)Data,"LED3:1")!=0)
	{
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,GPIO_PIN_SET);
	}
	if(strstr((char*)Data,"LED3:0")!=0)
	{
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,GPIO_PIN_RESET);
	}
	
	if(strstr((char*)Data,"BT=")!=0)//BT=500
	{
		BlinkTime=atoi(strstr((char*)Data,"BT=")+3);
		printf("BlinkTime:%d\r\n",BlinkTime);
	}
	
	if(strstr((char*)Data,"SW?")!=0)
	{
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
		{
			Log("KEY1:0\r\n");
		}
		else
		{
			Log("KEY1:1\r\n");
		}
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
		{
			Log("KEY2:0\r\n");
		}
		else
		{
			Log("KEY2:0\r\n");
		}
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
		{
			Log("KEY3:0\r\n");
		}
		else
		{
			Log("KEY3:1\r\n");
		}
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
		{
			Log("KEY4:0\r\n");
		}
		else
		{
			Log("KEY4:1\r\n");
		}
	}		
}


void Test6_Serial_RX(void)
{
	uint8_t KeyPressed[4]={0,0,0,0};
	if(HAL_UART_Receive_IT(&huart2, (uint8_t *)&NewDataInt, 1) != HAL_OK)
	{	  
	}
	  
	while(1)
	{
		if(NewDataLineCount>0)
		{
			printf("NewDataLine:%s\r\n",RXBuffer);
			Process_UART_Data(RXBuffer);
			NewDataLineCount=0;
			
		}
		
		
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET && KeyPressed[0]==0)
		{
			Log("KEY1:0\r\n");
			KeyPressed[0]=1;
		}
		else if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_SET && KeyPressed[0]==1)
		{
			Log("KEY1:1\r\n");
			KeyPressed[0]=0;
		}
		
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET && KeyPressed[1]==0)
		{
			Log("KEY2:0\r\n");
			KeyPressed[1]=1;
		}
		else if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_SET && KeyPressed[1]==1)
		{
			Log("KEY2:1\r\n");
			KeyPressed[1]=0;
		}
		
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET && KeyPressed[2]==0)
		{
			Log("KEY3:0\r\n");
			KeyPressed[2]=1;
		}
		else if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_SET && KeyPressed[2]==1)
		{
			Log("KEY3:1\r\n");
			KeyPressed[2]=0;
		}
		
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET && KeyPressed[3]==0)
		{
			Log("KEY4:0\r\n");
			KeyPressed[3]=1;
		}
		else if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_SET && KeyPressed[3]==1)
		{
			Log("KEY4:1\r\n");
			KeyPressed[3]=0;
		}
		
		HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
		HAL_Delay(BlinkTime);
	}
}




void MyApp(void)
{	
	HAL_UART_Transmit(&huart2,(uint8_t*)"Test_Serial_RX",14,100);
	
	//CDC_Transmit_FS((uint8_t*)"Test_CDC\r\n",10);

	Test6_Serial_RX();
	
	
	while(1)
	{
			
	}
	
	
}
