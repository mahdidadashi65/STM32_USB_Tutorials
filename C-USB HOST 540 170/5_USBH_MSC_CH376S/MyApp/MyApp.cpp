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

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif



#include <Ch376msc.h>


#define printInfo printf

//..............................................................................................................................
// Connect to SPI port: MISO, MOSI, SCK
Ch376msc flashDrive(0,0,0); // chipSelect, busy pins (use this if no other device are attached to SPI port(MISO pin used as interrupt))

//If the SPI port shared with other devices e.g SD card, display, etc. remove from comment the code below and put the code above in a comment
//Ch376msc flashDrive(10, 9, 8); // chipSelect, busy, interrupt pins
//..............................................................................................................................
 // buffer for reading
char adatBuffer[255];// max length 255 = 254 char + 1 NULL character
//..............................................................................................................................
// strings for writing to file
char adat[]="Vivamus nec nisl molestie, blandit diam vel, varius mi. Fusce luctus cursus sapien in vulputate.\n";
char adat2[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis efficitur ac est eu pharetra. \n";
//..............................................................................................................................
unsigned long totSect = 0;
unsigned long freeSect = 0;
uint8_t percentg = 0;
uint8_t tmpCommand; //used to store data coming from serial port
bool readMore;


void setup() {
  //Serial.begin(115200);
  flashDrive.init();
  printInfo("h:Print this help\n\n1:Create\n2:Append\n3:Read\n4:Read date/time\n"
		  "5:Modify date/time\n6:Delete\n7:List dir\n8:Print free space");
}

HAL_StatusTypeDef st;

void loop() 
{
	st= HAL_UART_Receive(&huart2,&tmpCommand,1,100);
  if(st==HAL_OK)
	{
    //tmpCommand = Serial.read();                      //read incoming bytes from the serial monitor
    if(((tmpCommand > 48)&&(tmpCommand < 58)) && !flashDrive.checkDrive()){ // if the data is ASCII 0 - 9 and no flash drive are attached
       printInfo("Attach flash drive first!");
      tmpCommand = 10; // change the command byte
    }
     switch (tmpCommand) {

      case 49: //1
        printInfo("COMMAND1: Create and write data to file : TEST1.TXT");    // Create a file called TEST1.TXT
          flashDrive.setFileName("TEST1.TXT");  //set the file name
          flashDrive.openFile();                //open the file

          for(int a = 0; a < 20; a++){          //write text from string(adat) to flash drive 20 times
            flashDrive.writeFile(adat, strlen(adat)); //string, string length
          }
          flashDrive.closeFile();               //at the end, close the file
        printInfo("Done!");
        break;
//*****************************************************************************************************************************************************
      case 50: //2
        printInfo("COMMAND2: Append data to file: TEST1.TXT");               // Append data to the end of the file.
        flashDrive.setFileName("TEST1.TXT");  //set the file name
        flashDrive.openFile();                //open the file
        flashDrive.moveCursor(CURSOREND);     //move the "virtual" cursor at end of the file, with CURSORBEGIN we actually rewrite our old file
        //flashDrive.moveCursor(flashDrive.getFileSize()); // is almost the same as CURSOREND, because we put our cursor at end of the file

        for(int a = 0; a < 20; a++){          //write text from string(adat) to flash drive 20 times
        	if(flashDrive.getFreeSectors()){ //check the free space on the drive
        		flashDrive.writeFile(adat2, strlen(adat2)); //string, string length
        	} else {
        		printf("Disk full\r\n");
        	}
        }
        flashDrive.closeFile();               //at the end, close the file
        printInfo("Done!");
        break;
//*****************************************************************************************************************************************************
      case 51: //3
        printInfo("COMMAND3: Read File: TEST1.TXT");                         // Read the contents of this file on the USB disk, and display contents in the Serial Monitor
        flashDrive.setFileName("TEST1.TXT");  //set the file name
        flashDrive.openFile();                //open the file
        readMore = true;
                //read data from flash drive until we reach EOF
        while(readMore)
		{ // our temporary buffer where we read data from flash drive and the size of that buffer
        	readMore = flashDrive.readFile(adatBuffer, sizeof(adatBuffer));
        	printf("%s\r\n",adatBuffer);          //print the contents of the temporary buffer
        }
        flashDrive.closeFile();               //at the end, close the file
        printInfo("Done!");
        break;
//*****************************************************************************************************************************************************
      case 52: //4
        printInfo("COMMAND4: Read File date/time: TEST1.TXT");      // Read the date and time of file, default 2004.01.01 - 00:00:00
        flashDrive.setFileName("TEST1.TXT");            //set the file name
        flashDrive.openFile();                          //open the file
                //print informations about the file
          printf("%s\r\n",flashDrive.getFileName());
          printf("%d",flashDrive.getYear());
          printf("y\t");
          printf("%d",flashDrive.getMonth());
          printf("m\t");
          printf("%d",flashDrive.getDay());
          printf("d\t");
          printf("%d",flashDrive.getHour());
          printf("h\t");
          printf("%d",flashDrive.getMinute());
          printf("m\t");
          printf("%d",flashDrive.getSecond());
          printf("s\r\n");
        flashDrive.closeFile();                         //at the end, close the file
        printInfo("Done!");
        break;
//*****************************************************************************************************************************************************
      case 53: //5
        printInfo("COMMAND5: Modify File date/time: TEST1.TXT");    // Modify the file date/time and save
        flashDrive.setFileName("TEST1.TXT");  //set the file name
        flashDrive.openFile();                //open the file

          flashDrive.setYear(2019);
          flashDrive.setMonth(2);
          flashDrive.setDay(24);
          flashDrive.setHour(15);
          flashDrive.setMinute(47);
          flashDrive.setSecond(26);

          flashDrive.dirInfoSave();           //save the changed data
        flashDrive.closeFile();               //and yes again, close the file after when you don`t use it
        printInfo("Done!");
        break;
//*****************************************************************************************************************************************************
      case 54: //6
        printInfo("COMMAND6: Delete File: TEST1.TXT");                       // Delete the file named TEST1.TXT
        flashDrive.setFileName("TEST1.TXT");  //set the file name
        flashDrive.deleteFile();              //delete file
        printInfo("Done!");
        break;
//*****************************************************************************************************************************************************
      case 55: //7
        printInfo("COMMAND7: List root directory");                          //Print all file names in the current directory
          while(flashDrive.listDir()){ // reading next file
            printf("%s",flashDrive.getFileName()); // get the actual file name
            printf(" : ");
             printf("%d",flashDrive.getFileSize()); // get the actual file size in bytes
            printf(" >>>\t");
             printf("%d\r\n",flashDrive.getFileSizeStr()); // get the actual file size in formatted string
          }
          printInfo("Done!");
        break;
//*****************************************************************************************************************************************************
      case 56: //8
    	  totSect = flashDrive.getTotalSectors(); // get the total sector number
    	  freeSect = flashDrive.getFreeSectors(); // get the available sector number
//    	  percentg = map(freeSect,totSect,0,0,100); 		// convert it to percentage (0-100)
//    	  Serial.print("Disk size in bytes: ");
//    	  /*if the sector number is more than 8388607 (8388607 * 512 = 4294966784 byte = 4Gb (fits in a 32bit variable) )
//    	    							 e.g. 8388608 * 512 = 4294967296 byte (32bit variable overflows) */
//    	  if(totSect > 8388607){
//    		  Serial.print(">4Gb");
//    	  } else {
//        	  Serial.print(totSect * SECTORSIZE);
//    	  }
//    	  Serial.print("\tFree space in bytes: ");
//    	  if(freeSect > 8388607){
//    		  Serial.print(">4Gb");
//    	  } else {
//        	  Serial.print(freeSect * SECTORSIZE);
//    	  }
    	  printf("\tDisk usage :");
    	  printf("%d",percentg);
    	  printf("%%");
    	  switch (flashDrive.getFileSystem()) { //1-FAT12, 2-FAT16, 3-FAT32
			case 1:
				printf("\tFAT12 partition");
				break;
			case 2:
				printf("\tFAT16 partition");
				break;
			case 3:
				printf("\tFAT32 partition");
				break;
			default:
				printf("\tNo valid partition");
				break;
		}
    	 break;
//*****************************************************************************************************************************************************
      case 104: //h
    	  printInfo("h:Print this help\n\n1:Create\n2:Append\n3:Read\n4:Read date/time\n"
    			  "5:Modify date/time\n6:Delete\n7:List dir\n8:Print free space");
        break;
      default:
        break;
    }//end switch

  }//endif serial available

}//end loop

//Print information
//void printInfo(const char* info)
//{
//  char * infoPtr = info;
//  int infoLength = 0;
//    while(*infoPtr){
//      infoPtr++;
//      infoLength++;
//    }
//    Serial.print("\n\n");
//    for(int a = 0; a < infoLength; a++){
//      Serial.print('*');
//    }
//   Serial.println();
//   Serial.println(info);
//   for(int a = 0; a < infoLength; a++){
//      Serial.print('*');
//    }
//   Serial.print("\n\n");
//}



void MyApp(void)
{	
	printf("Test_SCH376\r\n");
	setup();
	
	while(1)
	{
		
		loop();
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		HAL_Delay(100);
	}
	
	
}
