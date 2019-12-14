
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



int KeyPressCount=0;
GPIO_PinState KeyState[2];
int KeyState_Last[2]={0,0};


void Test1(void)
{
	int Key1State;
	while(1)
	{
	  GPIO_PinState Key1State;
	  Key1State = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);	  
	  if(Key1State == GPIO_PIN_RESET)
	  //if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == GPIO_PIN_RESET)
	  {
		  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
	  }
	  else
	  {
		  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	  }
	  
	  HAL_Delay(100);
	}
}


void Test2(void)
{
	int Key1State;
	int Key2State;
	while(1)
	{
	  Key1State = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);	  
	  if(Key1State == GPIO_PIN_RESET)
	  {
		  KeyPressCount++;
	  }	  
	  
	  
	  Key2State = HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin);	  
	  if(Key2State == GPIO_PIN_RESET)
	  {
		  KeyPressCount--;
	  }	 
	 
	  
	  HAL_Delay(10);
	}
}


void Test3(void)
{
	while(1)
	{
		KeyState[0] = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);	  
		if((KeyState[0] == GPIO_PIN_RESET) && (KeyState_Last[0]==0))
		{
			KeyState_Last[0]=1;
			KeyPressCount++;
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
	
	Test1();
	//Test2();
	//Test3();
	
	while(1)
	{
			
	}
	
	
}
