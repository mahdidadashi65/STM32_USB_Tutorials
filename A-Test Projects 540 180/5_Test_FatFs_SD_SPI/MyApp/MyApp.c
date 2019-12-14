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

#include "fatfs.h"


extern UART_HandleTypeDef huart2;

extern uint8_t retUSER;    /* Return value for USER */
extern  char USERPath[4];   /* USER logical drive path */
extern  FATFS USERFatFS;    /* File system object for USER logical drive */
extern  FIL USERFile;       /* File object for USER */



  uint32_t byteswritten, bytesread;                     /* File write/read counts */
  uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
  uint8_t rtext[100]; 
  

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


void Test_FatFs_Write(void)
{
	
	if(f_open(&USERFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
        {
          /* 'STM32.TXT' file Open for write Error */
          printf("STM32.TXT file Open for write Error\r\n");
        }
        else
        {
          /*##-5- Write data to the text file ################################*/
          retUSER = f_write(&USERFile, wtext, sizeof(wtext), (void *)&byteswritten);

          /*##-6- Close the open text file #################################*/
          if (f_close(&USERFile) != FR_OK )
          {
            printf("f_close Error\r\n");
          }
          
          if((byteswritten == 0) || (retUSER != FR_OK))
          {
            /* 'STM32.TXT' file Write or EOF Error */
            printf("STM32.TXT file Write or EOF Error\r\n");
          }
		  else
		  {
			 printf("Test_FatFs_Write OK\r\n"); 
		  }
	  }
  
}

void Test_FatFs_Read(void)
{
	
	/*##-7- Open the text file object with read access ###############*/
            if(f_open(&USERFile, "STM32.TXT", FA_READ) != FR_OK)
            {
              /* 'STM32.TXT' file Open for read Error */
				printf("STM32.TXT file Open for read Error\r\n");
            }
            else
            {
              /*##-8- Read data from the text file ###########################*/
              retUSER = f_read(&USERFile, rtext, sizeof(rtext), (UINT*)&bytesread);
              
              if((bytesread == 0) || (retUSER != FR_OK))
              {
                /* 'STM32.TXT' file Read or EOF Error */
				  printf("STM32.TXT file Read or EOF Error\r\n");
              }
              else
              {
                /*##-9- Close the open text file #############################*/
                f_close(&USERFile);
                
                /*##-10- Compare read data with the expected data ############*/
                if((bytesread != byteswritten))
                {                
                  /* Read data is different from the expected data */
                  
					printf("Read data is different from the expected data\r\n");
                }
                else
                {
                  /* Success of the demo: no error occurrence */
                  printf("Test_FatFs_Read OK\r\n");
                }
			}
		}
}

void MyApp(void)
{	
	printf("Test_SD_SPI_FatFs\r\n");
	
	if(HAL_GPIO_ReadPin(uSD_SW_GPIO_Port,uSD_SW_Pin)==GPIO_PIN_SET)
	{
		printf("Err uSD Not Found\r\n");
		
		while(1)
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			HAL_Delay(100);			
		}
	
	}
	
	
	
	if(f_mount(&USERFatFS, (TCHAR const*)USERPath, 0) != FR_OK)
    {
      /* FatFs Initialization Error */
         printf("FatFs Initialization Error\r\n");
		
		while(1)
		{
			HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
			HAL_Delay(100);			
		}
    }
	
	
	Test_FatFs_Write();
	Test_FatFs_Read();

	
	while(1)
	{
			
	}
	
	
}
