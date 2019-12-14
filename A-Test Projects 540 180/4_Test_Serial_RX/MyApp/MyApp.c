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
   HAL_UART_Transmit(&huart2,(uint8_t*)log,strlen(log),100);	
}


void Test1_Serial_RX(void)
{
	uint8_t NewData[2];
	HAL_StatusTypeDef Status;
	while(1)
	{
	    Status=HAL_UART_Receive(&huart2,NewData,1,100);
		if(Status==HAL_OK)
		{
			printf("NewData:%c\r\n",NewData[0]);
			if(NewData[0]=='S')
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
				printf("LED ON\r\n");
			}
			if(NewData[0]=='R')
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
				printf("LED OFF\r\n");
			}
		}
	  HAL_Delay(10);
	}
}

void Test2_Serial_RX(void)
{
	uint8_t NewData;
	HAL_StatusTypeDef Status;
	while(1)
	{
	    Status=HAL_UART_Receive(&huart2,&NewData,1,100);
		if(Status==HAL_OK)
		{
			printf("NewData:%c\r\n",NewData);
			if(NewData=='S')
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
				printf("LED ON\r\n");
			}
			if(NewData=='R')
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
				printf("LED OFF\r\n");
			}
		}
	  HAL_Delay(10);
	}
}



//uint8_t NewDataInt;
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//   printf("NewDataInt:%c\r\n",NewDataInt);
//	
//	if(NewDataInt=='S')
//	{
//		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
//		printf("LED ON\r\n");
//	}
//	if(NewDataInt=='R')
//	{
//		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
//		printf("LED OFF\r\n");
//	}
//	
//	HAL_UART_Receive_IT(&huart2,&NewDataInt,1);
//	
//}

//void Test3_Serial_RX(void)
//{	
//	HAL_StatusTypeDef Status;	
//	Status=HAL_UART_Receive_IT(&huart2,&NewDataInt,1);
//	
//	while(1)
//	{
//		
//		
//	  HAL_Delay(10);
//	}
//}


///////////////////////////////////////
//uint8_t NewDataInt;
//uint8_t NewDataReady=0;
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance==USART2)
//	{
//		NewDataReady=1;
//		HAL_UART_Receive_IT(&huart2,&NewDataInt,1);
//	}	
//}

//void Test4_Serial_RX(void)
//{	
//	HAL_StatusTypeDef Status;	
//	Status=HAL_UART_Receive_IT(&huart2,&NewDataInt,1);
//	
//	while(1)
//	{		
//		if(NewDataReady>0)
//		{
//		    printf("NewDataInt:%c\r\n",NewDataInt);
//	
//			if(NewDataInt=='S')
//			{
//				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
//				printf("LED ON\r\n");
//			}
//			if(NewDataInt=='R')
//			{
//				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
//				printf("LED OFF\r\n");
//			}
//			
//			NewDataReady=0;
//		}
//	
//	  HAL_Delay(10);
//	}
//}


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

//void ProcessUartData(uint8_t* Data)
//{
//			if(strstr((char*)Data,"LED1:1")!=0)
//			{
//				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
//				printf("LED ON\r\n");
//			}
//			if(strstr((char*)Data,"LED1:0")!=0)
//			{
//				HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
//				printf("LED OFF\r\n");
//			}
//}

//void Test5_Serial_RX(void)
//{	
//	HAL_StatusTypeDef Status;	
//	Status=HAL_UART_Receive_IT(&huart2,&NewDataInt,1);
//	
//	while(1)
//	{		
//		if(NewDataLineCount>0)
//		{
//		    printf("NewDataLine:%s\r\n",RXBuffer);
//			ProcessUartData(RXBuffer);
//			NewDataLineCount=0;
//		}
//	
//	  HAL_Delay(10);
//	}
//}



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
			HAL_UART_Transmit(&huart2,"KEY1:0\r\n",8,100);
		}
		else
		{
			HAL_UART_Transmit(&huart2,"KEY1:1\r\n",8,100);
		}
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
		{
			HAL_UART_Transmit(&huart2,"KEY2:0\r\n",7,100);
		}
		else
		{
			HAL_UART_Transmit(&huart2,"KEY2:1\r\n",7,100);
		}
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)
		{
			HAL_UART_Transmit(&huart2,"KEY3:0\r\n",7,100);
		}
		else
		{
			HAL_UART_Transmit(&huart2,"KEY3:1\r\n",7,100);
		}
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET)
		{
			HAL_UART_Transmit(&huart2,"KEY4:0\r\n",7,100);
		}
		else
		{
			HAL_UART_Transmit(&huart2,"KEY4:1\r\n",7,100);
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
			HAL_UART_Transmit(&huart2,"KEY1:0\r\n",7,100);
			KeyPressed[0]=1;
		}
		else if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_SET && KeyPressed[0]==1)
		{
			HAL_UART_Transmit(&huart2,"KEY1:1\r\n",7,100);
			KeyPressed[0]=0;
		}
		
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET && KeyPressed[1]==0)
		{
			HAL_UART_Transmit(&huart2,"KEY2:0\r\n",7,100);
			KeyPressed[1]=1;
		}
		else if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_SET && KeyPressed[1]==1)
		{
			HAL_UART_Transmit(&huart2,"KEY2:1\r\n",7,100);
			KeyPressed[1]=0;
		}
		
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET && KeyPressed[2]==0)
		{
			HAL_UART_Transmit(&huart2,"KEY3:0\r\n",7,100);
			KeyPressed[2]=1;
		}
		else if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_SET && KeyPressed[2]==1)
		{
			HAL_UART_Transmit(&huart2,"KEY3:1\r\n",7,100);
			KeyPressed[2]=0;
		}
		
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_RESET && KeyPressed[3]==0)
		{
			HAL_UART_Transmit(&huart2,"KEY4:0\r\n",7,100);
			KeyPressed[3]=1;
		}
		else if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==GPIO_PIN_SET && KeyPressed[3]==1)
		{
			HAL_UART_Transmit(&huart2,"KEY4:1\r\n",7,100);
			KeyPressed[3]=0;
		}
		
		HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
		HAL_Delay(BlinkTime);
	}
}




void MyApp(void)
{	
	HAL_UART_Transmit(&huart2,(uint8_t*)"Test_Serial_RX",14,100);
	
	//Test1_Serial_RX();
	//Test2_Serial_RX();
	//Test3_Serial_RX();
	//Test4_Serial_RX();
	//Test5_Serial_RX();
	Test6_Serial_RX();
	
	
	while(1)
	{
			
	}
	
	
}
