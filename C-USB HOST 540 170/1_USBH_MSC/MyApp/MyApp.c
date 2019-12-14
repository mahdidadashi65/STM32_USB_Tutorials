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

extern ApplicationTypeDef Appli_state;

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



void Test_USBH_FatFs_Write(void)
{
	uint32_t byteswritten;
	 uint8_t wtext[] = "This is STM32 working with FatFs";
	
		if(f_open(&USBHFile, "USBFILE.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
        {
         printf("Err f_open\r\n");
        }
        else
        {
          /*##-5- Write data to the text file ################################*/
          retUSBH = f_write(&USBHFile, wtext, sizeof(wtext), (void *)&byteswritten);

          /*##-6- Close the open text file #################################*/
          if (f_close(&USBHFile) != FR_OK )
          {
            printf("Err f_close\r\n");
          }
		  
		  if((byteswritten == 0) || (retUSBH != FR_OK))
          {
            printf("Err file Write or EOF\r\n");
          }
		  else
		  {
			  printf("Test_FatFs_Write OK\r\n");
		  }
		}
	
	
}


void Test_USBH_FatFs_Read(void)
{
	uint32_t bytesread;
	uint8_t rtext[100];
	

		/*##-7- Open the text file object with read access ###############*/
            if(f_open(&USBHFile, "USBFILE.TXT", FA_READ) != FR_OK)
            {
              printf("Err f_open\r\n");
            }
            else
            {
              /*##-8- Read data from the text file ###########################*/
              retUSBH = f_read(&USBHFile, rtext, sizeof(rtext), (UINT*)&bytesread);
              
              if((bytesread == 0) || (retUSBH != FR_OK))
              {
                printf("Err file Read or EOF\r\n");
              }
              else
              {
                /*##-9- Close the open text file #############################*/
                f_close(&USBHFile);
                
                printf("Test_FatFs_Read OK\r\n");
				printf("[%s]\r\n",rtext);
              }
            }
	
}

ApplicationTypeDef Last_Appli_state;

void Test1(void)
{
	
	if((Appli_state == APPLICATION_READY) && (Last_Appli_state!=APPLICATION_READY))
	{
		Last_Appli_state=APPLICATION_READY;
		Test_USBH_FatFs_Write();
		Test_USBH_FatFs_Read();
	}
		
}

void MyApp(void)
{
	printf("Start USB HOST OK\r\n");
	
  while (1)
  {
     MX_USB_HOST_Process();
	 HAL_Delay(100);
	 HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin); 
	  
	  Test1();
	  
	  
  }
}	


