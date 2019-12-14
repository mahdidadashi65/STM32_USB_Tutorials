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
			char path[100];
	sprintf(path,"%s%s",USBHPath,"USBFILE.TXT");
		if(f_open(&USBHFile, path, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
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
			  printf("Test_USBH_FatFs_Write OK\r\n");
		  }
		}
	
	
}


void Test_USBH_FatFs_Read(void)
{
	uint32_t bytesread;
	uint8_t rtext[100];
			char path[100];
	sprintf(path,"%s%s",USBHPath,"USBFILE.TXT");

		/*##-7- Open the text file object with read access ###############*/
            if(f_open(&USBHFile, path, FA_READ) != FR_OK)
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
                
                printf("Test_USBH_FatFs_Read OK\r\n");
				printf("[%s]\r\n",rtext);
              }
            }
	
}




void Test_SD_FatFs_Write(void)
{
	uint32_t byteswritten;
	 uint8_t wtext[] = "This is STM32 working with FatFs";
	char path[100];
	sprintf(path,"%s%s",USERPath,"SDFILE.TXT");
	
	retUSER=f_open(&USERFile, path, FA_CREATE_ALWAYS | FA_WRITE) ;
	    if(retUSER!= FR_OK)
        {
         printf("Err f_open\r\n");
        }
        else
        {
          /*##-5- Write data to the text file ################################*/
          retUSER = f_write(&USERFile, wtext, sizeof(wtext), (void *)&byteswritten);

          /*##-6- Close the open text file #################################*/
          if (f_close(&USERFile) != FR_OK )
          {
            printf("Err f_close\r\n");
          }
		  
		  if((byteswritten == 0) || (retUSER != FR_OK))
          {
            printf("Err file Write or EOF\r\n");
          }
		  else
		  {
			  printf("Test_SD_FatFs_Write OK\r\n");
		  }
		}
	
	
}


void Test_SD_FatFs_Read(void)
{
	uint32_t bytesread;
	uint8_t rtext[100];
		char path[100];
	sprintf(path,"%s%s",USERPath,"SDFILE.TXT");

		/*##-7- Open the text file object with read access ###############*/
            if(f_open(&USERFile, path, FA_READ) != FR_OK)
            {
              printf("Err f_open\r\n");
            }
            else
            {
              /*##-8- Read data from the text file ###########################*/
              retUSER = f_read(&USERFile, rtext, sizeof(rtext), (UINT*)&bytesread);
              
              if((bytesread == 0) || (retUSER != FR_OK))
              {
                printf("Err file Read or EOF\r\n");
              }
              else
              {
                /*##-9- Close the open text file #############################*/
                f_close(&USERFile);
                
                printf("Test_SD_FatFs_Read OK\r\n");
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
	
	
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
	{
		Test_SD_FatFs_Write();
	    Test_SD_FatFs_Read();
		HAL_Delay(2000);
	}
	
	
		
}


int MakeDir(char* path)
{
	 int i;
	 FRESULT res;
	 char mpath[100];

	 i=0;
	 while(path[i]!='\0')
	 {
		 mpath[i]=path[i];
		 i++;
		 mpath[i]=0;
		 if(path[i]=='/')
		 {
			 printf("f_mkdir:%s\r\n",mpath);
			res = f_mkdir(mpath);
			if (res != FR_OK)
			{
				if (res == FR_EXIST)
				{
					printf("FR_EXIST\r\n");
				}
				else
				{
					printf("Error MakeDir\r\n");
					//put_rc((FRESULT)res);
				}
			}
		 }
	 }
	 return 0;
 }
 
 
int CopyFile(char* SrcPath,char* DestPath)
{ 
	FIL WriteFile,ReadFile;	 
    uint8_t CopyBuff[1024] __attribute__ ((aligned (4)));
	FRESULT res,res1,res2;
	uint32_t p1;

	int s1, s2, cnt,j, blen = sizeof(CopyBuff);
	 
//	if(f_mount(&USBHFatFS, USBHPath, 0) != FR_OK)
//    {  
//		printf("ERROR : Cannot Initialize USBHFatFS! \n");
//    }
	
	 printf("CopyFrom:%s\r\n",SrcPath);

	res = f_open(&ReadFile, SrcPath, FA_OPEN_EXISTING | FA_READ);
	if (res) 
	{
		printf("Err Open File1:%s\r\n",SrcPath);
	  return 1;
	}
	int SizeofFile = f_size(&ReadFile);
	printf("ReadFile Size on Src=%d\r\n", SizeofFile);

	//MakeDir(DestPath);
	printf("CopyTo:%s\r\n",DestPath);
	res = f_open(&WriteFile, DestPath, FA_CREATE_ALWAYS | FA_WRITE);

	if (res)
	{
	   printf("Err Open File2:%s\r\n",DestPath);
	  return 1;
	}

	for (;;) 
	{
		res1 = f_read(&ReadFile, CopyBuff, blen, &s1);
		
		if (s1 < blen)
		{
			for (j=s1; j<blen; j++)
			CopyBuff [j] = 0;
		}

		res2 = f_write(&WriteFile, CopyBuff, s1, &s2);
		f_sync (&WriteFile);

		if (res1!=0) 
		{
			//put_rc(res1);
			break;   /* error  */
		}
		if ( s1 == 0) 
		{
			break;   /* error or eof */
		}
		
		p1 += s2;
		printf("%d Kbytes copied\r\n", p1/1024);
	  
		if ((res2!=0) || (s2 < s1))
		{
			printf("disk full\r\n");
			break ;   /* error or disk full */
		}
	}

	f_close(&ReadFile);
	f_close(&WriteFile);

	printf("Copy finished\r\n");

//	if(f_mount(&USBHFatFS, "", 0) != FR_OK)
//	{  
//		printf("ERROR : Cannot Relase FatFs! \r\n");
//	}
	return 1;
 }

char SrcPath[100];
char DestPath[100];

void Test2(void)
{
	
	if(Appli_state == APPLICATION_READY)
	{	
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)
		{
		        sprintf(SrcPath,"%s%s",USERPath,"SDFile.txt");	
                sprintf(DestPath,"%s%s",USBHPath,"SDFile2.txt");
				printf("CopyFile From:%s to %s\r\n",SrcPath,DestPath);				
			    CopyFile(SrcPath,DestPath);	
		}
		
		
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)
		{
			    sprintf(SrcPath,"%s%s",USBHPath,"USBFile.txt");	
				sprintf(DestPath,"%s%s",USERPath,"USBFile2.txt");
				printf("CopyFile From:%s to %s\r\n",SrcPath,DestPath);
				CopyFile(SrcPath,DestPath);
		}
	}
	
}



void MyApp(void)
{
	printf("Start USB HOST OK\r\n");
	
		printf("Start Test FatFs\r\n");
	
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
      printf("Err uSD mount\r\n");
		while(1)
		{
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			HAL_Delay(100);
		}
    }
	
  while (1)
  {
     MX_USB_HOST_Process();
	 HAL_Delay(100);
	 HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin); 
	  
	  //Test1();
	  Test2();
	  
  }
}	


