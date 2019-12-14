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

int KeyPressCount=0;
GPIO_PinState KeyState[2];
int KeyState_Last[2]={0,0};

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

void Test1_Serial_TX(void)
{
	while(1)
	{
		KeyState[0] = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);	  
		if((KeyState[0] == GPIO_PIN_RESET) && (KeyState_Last[0]==0))
		{
			KeyState_Last[0]=1;
			KeyPressCount++;
			Log("UP\r\n");
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
			Log("Down\r\n");
		}	
		else if((KeyState[1] == GPIO_PIN_SET) && (KeyState_Last[1]==1))
		{
			KeyState_Last[1]=0;
		} 
	 
	  
	  HAL_Delay(10);
	}
}

void Test2_Serial_TX(void)
{
	char Buff[20];
	while(1)
	{
		KeyState[0] = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);	  
		if((KeyState[0] == GPIO_PIN_RESET) && (KeyState_Last[0]==0))
		{
			KeyState_Last[0]=1;
			KeyPressCount++;
			sprintf(Buff,"Count:%d\r\n",KeyPressCount);
			Log(Buff);
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
			sprintf(Buff,"Count:%d\r\n",KeyPressCount);
			Log(Buff);
		}	
		else if((KeyState[1] == GPIO_PIN_SET) && (KeyState_Last[1]==1))
		{
			KeyState_Last[1]=0;
		} 
	 
	  
	  HAL_Delay(10);
	}
}

void Test3_Serial_TX(void)
{
	while(1)
	{
		KeyState[0] = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);	  
		if((KeyState[0] == GPIO_PIN_RESET) && (KeyState_Last[0]==0))
		{
			KeyState_Last[0]=1;
			KeyPressCount++;
			printf("Count:%d\r\n",KeyPressCount);
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
			printf("Count:%d\r\n",KeyPressCount);
		}	
		else if((KeyState[1] == GPIO_PIN_SET) && (KeyState_Last[1]==1))
		{
			KeyState_Last[1]=0;
		} 
	 
	  
	  HAL_Delay(10);
	}
}
void Test4_Serial_TX(void)
{
	int INTVAL=24;
	float FLOATVAL = 123.456;
	char  CHARVAL = 'M';
	char* STRINGVAL = "Hello World";	
	uint32_t HEXVAL=0xAE3456;
	
	while(1)
	{
		KeyState[0] = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);	  
		if((KeyState[0] == GPIO_PIN_RESET) && (KeyState_Last[0]==0))
		{
			KeyState_Last[0]=1;
			KeyPressCount++;
			
			printf("INTVAL:%d\r\n",INTVAL);
			printf("FLOATVAL:%f\r\n",FLOATVAL);
			printf("CHARVAL:%c\r\n",CHARVAL);
			printf("STRINGVAL:%s\r\n",STRINGVAL);
			printf("HEXVAL:%x\r\n",HEXVAL);
			printf("HEXVAL:%X\r\n",HEXVAL);			
			printf("Percent:%% \\ \r\n");
			printf("INTVAL:%d  FLOATVAL:%f \r\n",INTVAL,FLOATVAL);
			printf("INTVAL:%d  FLOATVAL:%.1f \r\n",INTVAL,FLOATVAL);
			
			printf("INTVAL:%04d\r\n",INTVAL);
			printf("HEXVAL:%08X\r\n",HEXVAL);	
			
			
			
			
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
			printf("Count:%d\r\n",KeyPressCount);
		}	
		else if((KeyState[1] == GPIO_PIN_SET) && (KeyState_Last[1]==1))
		{
			KeyState_Last[1]=0;
		} 
	 
	  
	  HAL_Delay(10);
	}
}

void MyApp(void)
{	
	HAL_UART_Transmit(&huart2,(uint8_t*)"Test_Serial_TX",14,100);
	
	//Test1_Serial_TX();
	//Test2_Serial_TX();
	//Test3_Serial_TX();
	Test4_Serial_TX();
	
	while(1)
	{
			
	}
	
	
}
