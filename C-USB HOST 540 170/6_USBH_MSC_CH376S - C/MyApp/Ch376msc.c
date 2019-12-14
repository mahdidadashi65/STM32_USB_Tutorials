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




/*
 * Ch376msc.cpp
 *
 *  Created on: Feb 25, 2019
 *      Author: György Kovács
 *
 *
 *
 */

#include "Ch376msc.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>




typedef enum commInterface{
	UART,
	SPII
}commInterface;

typedef enum fileProcessENUM { // for file read/write state machine
	REQUEST,
	NEXT,
	READWRITE,
	DONE
}fileProcessENUM;

	///////////************/////////////
	typedef	union fSizeContainer
		{
			uint8_t b[4]; //byte
			uint32_t value; //unsigned long
		}fSizeContainer;
		////////////////
		///https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system

	typedef	struct fatFileInfo{
			char name[11];//11
			uint8_t fattr;//1
			uint8_t uattr;//1
			uint8_t del;  //1
			uint16_t crTime;//2
			uint16_t crDate;//2
			uint16_t ownId;//2
			uint16_t accRight;//2
			uint16_t modTime;//2
			uint16_t modDate;//2
			uint16_t startCl;//2
			uint32_t size;//4
		}fatFileInfo;
		///////////////
		typedef struct diskInfo{	//disk information
			uint32_t totalSector;	//the number of total sectors (low byte first)
			uint32_t freeSector;	//the number of free sectors (low byte first)
			uint8_t diskFat;			//FAT type: 0x01-FAT12, 0x02-FAT16, 0x03-FAT32
		}diskInfo;
		
		
		
			///////Global Variables///////////////////////////////
	bool _fileWrite = false; // read or write mode, needed for close operation
	bool _deviceAttached = false;	//false USB levalsztva, true csatlakoztatva
	bool _controllerReady = false; // ha sikeres a kommunikacio
	bool _hwSerial;

	uint8_t _byteCounter = 0; //vital variable for proper reading,writing
	uint8_t _answer = 0;	//a CH jelenlegi statusza INTERRUPT
	uint8_t _spiChipSelect; // chip select pin SPI
	uint8_t _spiBusy; //   busy pin SPI
	uint8_t _intPin; // interrupt pin
	uint16_t _sectorCounter = 0;// variable for proper reading
	uint32_t _speed; // Serial communication speed
	char _filename[12];

	//HardwareSerial* _comPortHW; // Serial interface
	//Stream* _comPort;

	commInterface _interface;
	fileProcessENUM fileProcesSTM = REQUEST;

	fatFileInfo _fileData;
	diskInfo _diskData;
	



extern SPI_HandleTypeDef hspi3;


extern TIM_HandleTypeDef htim6;


void delayMicroseconds(int Delayus)
{

	HAL_TIM_Base_Start(&htim6);
	volatile uint32_t start =__HAL_TIM_GET_COUNTER(&htim6);
	while((__HAL_TIM_GET_COUNTER(&htim6)-start)<=Delayus);
	HAL_TIM_Base_Stop(&htim6);
		
	
}

int millis(void)
{
	return HAL_GetTick();
}


uint8_t readSerDataUSB(){
//	uint32_t oldMillis = millis();
//		while (!_comPort->available()){ // wait until data is arrive
//			if ((millis()- oldMillis) > TIMEOUT){
//				return 0xFF; // Timeout valasz
//			}//end if
//		}//end while
//	return _comPort->read();
}

void write(uint8_t data){
	if(_interface == UART){
		//_comPort->write(data);
	} else { // SPI
		delayMicroseconds(3);//datasheet TSC min 1.5uSec
		spiReady();
		
		HAL_SPI_Transmit(&hspi3,&data,1,100);
		//	SPI.transfer(data);
		}
	}//end SPI

uint8_t spiReadData(){
	
	uint8_t DataOut,DataIn;
	delayMicroseconds(3);//datasheet TSC min 1.5uSec
	spiReady();
	
	DataOut=0;
	HAL_SPI_TransmitReceive(&hspi3,&DataOut,&DataIn,1,100);
	//return SPI.transfer(0x00);
	return DataIn;
}
void print(const char str[]){
	uint8_t stringCounter = 0;
	if(_interface == UART){
		//_comPort->print(str);
	} else { // SPI
		while(str[stringCounter]){ ///while not NULL
			write(str[stringCounter]);
			stringCounter++;
		}
	}
}

void spiReady(){
	uint32_t msTimeout;
	delayMicroseconds(3);
	msTimeout = millis();
	//while(digitalRead(_spiBusy))
	while(HAL_GPIO_ReadPin(CH376S_BUSY_GPIO_Port,CH376S_BUSY_Pin)==GPIO_PIN_SET)
	{
		if(millis()-msTimeout > TIMEOUT){
			break;
		}//end if
	}//end while
}

uint8_t spiWaitInterrupt(){
	uint8_t answ = 0xFF;
	uint32_t oldMillis = millis();
	//while(digitalRead(_intPin))
	while(HAL_GPIO_ReadPin(CH376S_INT_GPIO_Port,CH376S_INT_Pin)==GPIO_PIN_SET)	
	{
		if ((millis()- oldMillis) > TIMEOUT){
			answ = 0;//timeout occurred
			break;
		}//end if
	}//end while
	if(answ){
		answ = getInterrupt();
	}
	return answ;
}

uint8_t getInterrupt(){
	uint8_t _tmpReturn = 0;
	//spiWaitInterrupt();
		spiBeginTransfer();
		sendCommand(CMD_GET_STATUS);
		_tmpReturn = spiReadData();
		spiEndTransfer();
	return _tmpReturn;
}

void spiBeginTransfer(){
	spiReady();
//	SPI.beginTransaction(SPISettings(SPICLKRATE, MSBFIRST, SPI_MODE0));
//	digitalWrite(_spiChipSelect, LOW);
	
	HAL_GPIO_WritePin(CH376S_CS_GPIO_Port,CH376S_CS_Pin,GPIO_PIN_RESET);
	
}

void spiEndTransfer(){
//	digitalWrite(_spiChipSelect, HIGH);
//	SPI.endTransaction();
	
	HAL_GPIO_WritePin(CH376S_CS_GPIO_Port,CH376S_CS_Pin,GPIO_PIN_SET);
}



///////////////////////////////////////////



//////////////////SetGet////////////////////////////
bool Ch376msc_getDeviceStatus(){
	return _deviceAttached;
}
bool Ch376msc_getCHpresence(){
	return _controllerReady;
}
char* Ch376msc_getFileName(){
	strncpy(_filename,_fileData.name,11);//copy the filename string to internal filename variable
	_filename[11] = '\0';
	return _filename;
}
void Ch376msc_setFileName(const char* filename){
	strncpy(_filename,filename,12);//copy the filename string to internal filename variable
	Ch376msc_sendFilename(); // send to the CH376
}
uint8_t Ch376msc_getStatus(){
	return _answer;
}

uint32_t Ch376msc_getFileSize(){
	return _fileData.size;
}

char* Ch376msc_getFileSizeStr(){ // make formatted file size string from unsigned long
	// final string is declared as static, return value
	static char _fsizeString[10];// e.g 1023 byte\0 , 9 char long + NULL terminating char
								  // or 1023,9 Kb\0
	uint32_t ul_size = _fileData.size;
	float fl_size;
	char strNumber[7]; // e.g 1023,9\0 , temporary buffer
	if(ul_size >= 1048576){ // if the filesize is 1Mb or bigger
		fl_size = ul_size / 1048576.0;
		//dtostrf(fl_size, 1, 1, _fsizeString);//convert float to string
		sprintf(_fsizeString,"%1.1f",fl_size);
		strcat(_fsizeString," Mb");  // concatenate unit symbol
	} else if(ul_size >= 1024){ // if the filesize is in Kb range
		fl_size = ul_size / 1024.0;
		//dtostrf(fl_size, 1, 1, _fsizeString);//convert float to string
		sprintf(_fsizeString,"%1.1f",fl_size);
		strcat(_fsizeString," Kb");
	} else { // if the filesize is in byte range
		//ltoa(ul_size, strNumber, 10);// convert long to string
		sprintf(strNumber,"%d",ul_size);
		strcpy(_fsizeString,strNumber);// copy to the final string
		strcat(_fsizeString," byte");// concatenate unit symbol
	}
	return _fsizeString; //return the final string
}

void Ch376msc_setYear(uint16_t year){ //Year(0 = 1980, 119 = 2099 supported under DOS/Windows, theoretically up to 127 = 2107)
	if(year > 2099) year = 2099;
	if(year < 1980) year = 1980;
	year -= 1980;
	constructDate(year, 0);
}

uint16_t Ch376msc_getYear(){
	uint16_t year = _fileData.modDate;
	year = year>> 9;
	year += 1980;
	return year;
}
void Ch376msc_setMonth(uint16_t month){
	if(month > 12) month = 12;
	if(month < 1) month = 1;
	constructDate(month, 1);
}
uint16_t Ch376msc_getMonth(){
	uint16_t month = _fileData.modDate;
	month = month << 7;
	month = month >> 12;
	return month;
}
void Ch376msc_setDay(uint16_t day){
	if(day > 31) day = 31;
	if(day < 1) day = 1;
	constructDate(day, 2);
}
uint16_t Ch376msc_getDay(){
	uint16_t day = _fileData.modDate;
	day = day << 11;
	day = day >> 11;
	return day;
}
//
void Ch376msc_setHour(uint16_t hour){ //Coordinated Universal Time (UTC)
	if(hour > 23) hour = 23;
	constructTime(hour, 0);
}

uint16_t Ch376msc_getHour(){
	uint16_t hour = _fileData.modTime;
	hour = hour >> 11;
	return hour;
}
void Ch376msc_setMinute(uint16_t minute){
	if(minute > 59) minute = 59;
	constructTime(minute, 1);
}
uint16_t Ch376msc_getMinute(){
	uint16_t minute = _fileData.modTime;
	minute = minute << 5;
	minute = minute >> 10;
	//_tempInteger *= 2;
	return minute;
}
void Ch376msc_setSecond(uint16_t second){ //! 0-58 2sec steps
	if(second > 59) second = 59;
	second /= 2;
	constructTime(second, 2);
}
uint16_t Ch376msc_getSecond(){
	uint16_t second = _fileData.modTime;
	second = second << 11;
	second = second >> 11;
	second *= 2;
	return second;
}
///////////////////////////////////

void constructDate(uint16_t value, uint8_t ymd){ // 0-year, 1-month, 2-day
	uint16_t tmpInt = _fileData.modDate;
	uint16_t year;
	uint16_t month;
	uint16_t day;
	/*<------- 0x19 --------> <------- 0x18 -------->
	 *15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
	 *y  y  y  y  y  y  y  m  m  m  m  d  d  d  d  d
	 */

	year = tmpInt >> 9;
	year = year << 9;

	month = tmpInt << 7;
	month = month >> 12;
	month = month << 5;

	day = tmpInt << 11;
	day = day >> 11;

	switch (ymd) {
		case 0://year
			year = value;
			year = year << 9;
			break;
		case 1://month
			month = value;
			month = month << 5;
			break;
		case 2://day
			day = value;
			break;
		default:
			break;
	}//end switch
	_fileData.modDate = year + month + day;
}

void constructTime(uint16_t value, uint8_t hms){
	uint16_t tmpInt = _fileData.modTime;
	uint16_t hour;
	uint16_t minute;
	uint16_t second;
	/*<------- 0x17 --------> <------- 0x16 -------->
	 *15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
	 *h  h  h  h  h  m  m  m  m  m  m  s  s  s  s  s
	 */

	hour = tmpInt >> 11; //cut minute and second
	hour = hour << 11; // set hour

	minute = tmpInt << 5; // cut hour
	minute = minute >> 10;// cut seconds
	minute = minute << 5; // set minute

	second = tmpInt << 11; // cut hour and minute
	second = second >> 11; // set second

	switch (hms) {
		case 0://hour
			hour = value;
			hour = hour << 11;
			break;
		case 1://minute
			minute = value;
			minute = minute << 5;
			break;
		case 2://second
			second = value;
			break;
		default:
			break;
	}//end switch
	_fileData.modTime = hour + minute + second;
}
//////////////////////////////////////////////////////
uint32_t Ch376msc_getTotalSectors(){ // disk(partition?) size in bytes = totalSector * SECTORSIZE
	return _diskData.totalSector;
}
//////////////////////////////////////////////////////
uint32_t Ch376msc_getFreeSectors(){ // total free bytes = freeSector * SECTORSIZE
	return _diskData.freeSector;
}
//////////////////////////////////////////////////////
uint8_t Ch376msc_getFileSystem(){ //0x01-FAT12, 0x02-FAT16, 0x03-FAT32
	return _diskData.diskFat;
}


////////////////////////////////////////////////////////////////////////////////////////

extern void delayMicroseconds(int us);

//with HW serial
//Ch376msc_Ch376msc(HardwareSerial &usb, uint32_t speed) { // @suppress("Class members should be properly initialized")
//	_interface = UART;
//	_comPortHW = &usb;
//	_comPort = &usb;
//	_speed = speed;
//	_hwSerial = true;
//}
//with soft serial
//Ch376msc_Ch376msc(Stream &sUsb) { // @suppress("Class members should be properly initialized")
//	_interface = UART;
//	_comPort = &sUsb;
//	_speed = 9600;
//	_hwSerial = false;
//}

//with SPI, MISO as INT pin(the SPI is only available for CH376)
//Ch376msc_Ch376msc(uint8_t spiSelect, uint8_t busy){ // @suppress("Class members should be properly initialized")
//	_interface = SPII;
//	_intPin = MISO; // use the SPI MISO for interrupt JUST if no other device is using the SPI!!
//	_spiChipSelect = spiSelect;
//	_spiBusy = busy;
//	_speed = 0;
//}
//not tested wit other lib
//Ch376msc_Ch376msc(uint8_t spiSelect, uint8_t busy, uint8_t intPin){ // @suppress("Class members should be properly initialized")
//	_interface = SPII;
//	_intPin = intPin;
//	_spiChipSelect = spiSelect;
//	_spiBusy = busy;
//	_speed = 0;
//}

//Ch376msc_~Ch376msc() {
//	//  Auto-generated destructor stub
//}

/////////////////////////////////////////////////////////////////
void Ch376msc_init()
	{
		
		_interface = SPII;
		
	HAL_Delay(100);//wait for VCC to normalize
	if(_interface == SPII){
//		pinMode(_spiChipSelect, OUTPUT);
//		digitalWrite(_spiChipSelect, HIGH);
		
		HAL_GPIO_WritePin(CH376S_CS_GPIO_Port,CH376S_CS_Pin,GPIO_PIN_SET);
		
		//pinMode(_spiBusy, INPUT);
//		if(_intPin != MISO) pinMode(_intPin, INPUT_PULLUP);
//		SPI.begin();
		spiBeginTransfer();
		sendCommand(CMD_RESET_ALL);
		spiEndTransfer();
		HAL_Delay(40);
		spiReady();//wait for device
//		if(_intPin == MISO){ // if we use MISO as interrupt pin, then tell it for the device ;)
//			spiBeginTransfer();
//			sendCommand(CMD_SET_SD0_INT);
//			write(0x16);
//			write(0x90);
//			spiEndTransfer();
//		}//end if
	} else {//UART
//		if(_hwSerial) _comPortHW->begin(9600);// start with default speed
//		sendCommand(CMD_RESET_ALL);
//		HAL_Delay(60);// wait after reset command, according to the datasheet 35ms is required, but that was too short
//		if(_hwSerial){ // if Hardware serial is initialized
//			setSpeed(); // Dynamically setup the com speed
//		}
	}//end if UART
	_controllerReady = pingDevice();// check the communication
	setMode(MODE_HOST_1);
	Ch376msc_checkDrive();
}
/////////////////////////////////////////////////////////////////
void Ch376msc_setSpeed(){ //set communication speed for HardwareSerial and device
	if(_speed == 9600){ // default speed for CH
 // do nothing
	} else {
//		sendCommand(CMD_SET_BAUDRATE);
//		switch (_speed) {
//			case 19200:
//				_comPortHW->write(uint8_t(0x02));//detach freq. coef
//				_comPortHW->write(uint8_t(0xD9));//detach freq. constant
//				break;
//			case 57600:
//				_comPortHW->write(uint8_t(0x03));
//				_comPortHW->write(uint8_t(0x98));
//				break;
//			case 115200:
//				_comPortHW->write(uint8_t(0x03));
//				_comPortHW->write(uint8_t(0xCC));
//				break;
//			default:
//				_speed = 9600;
//				break;
//		}//end switch

//		_comPortHW->end();
//		_comPortHW->begin(_speed);
//		HAL_Delay(2);// according to datasheet 2ms

	}// end if

}

/////////////////////////////////////////////////////////////////
uint8_t pingDevice(){
	uint8_t _tmpReturn = 0;
	if(_interface == UART){
		sendCommand(CMD_CHECK_EXIST);
		write(0x01); // ez ertek negaltjat adja vissza
		if(readSerDataUSB() == 0xFE){
			_tmpReturn = 1;//true
		}
	} else {
		spiBeginTransfer();
		sendCommand(CMD_CHECK_EXIST);
		write(0x01); // ez ertek negaltjat adja vissza
		if(spiReadData() == 0xFE){
			_tmpReturn = 1;//true
		}
		spiEndTransfer();
	}
	return _tmpReturn;
}

/////////////////////////////////////////////////////////////////
uint8_t setMode(uint8_t mode){
	uint8_t _tmpReturn = 0;
	uint32_t oldMillis;
	if(_interface == UART)
		{
//		sendCommand(CMD_SET_USB_MODE);
//		write(mode);
//		_tmpReturn = readSerDataUSB();
//		oldMillis = millis();
//		while(!_comPort->available()){
//			//wait for the second byte 0x15 or 0x16 or timeout occurs
//			if((millis()- oldMillis) > TIMEOUT){
//				break;
//			}
//		}
	} else {//spi
		spiBeginTransfer();
		sendCommand(CMD_SET_USB_MODE);
		write(mode);
		_tmpReturn = spiReadData();
		spiEndTransfer();
		delayMicroseconds(40);
	}
	Ch376msc_checkDrive();
	return _tmpReturn; // success or fail
}

/////////////////////////////////////////////////////////////////
uint8_t Ch376msc_mount(){ // return ANSWSUCCESS or ANSWFAIL
	uint8_t _tmpReturn = 0;
	if(_interface == UART) {
		sendCommand(CMD_DISK_MOUNT);
		_tmpReturn = readSerDataUSB();
	} else {
		spiBeginTransfer();
		sendCommand(CMD_DISK_MOUNT);
		spiEndTransfer();
		_tmpReturn = getInterrupt();
	}
	return _tmpReturn;
}

/////////////////////////////////////////////////////////////////
bool Ch376msc_checkDrive(){ //always call this function to you know is it any media attached to the usb
	uint8_t _tmpReturn = 0;
		if(_interface == UART){
//			while(_comPort->available()){ // while is needed, after connecting media, the ch376 send 3 message(connect, disconnect, connect)
//				_tmpReturn = readSerDataUSB();
//			}//end while
		} else {//spi
			//if(!digitalRead(_intPin))
			if(HAL_GPIO_ReadPin(CH376S_INT_GPIO_Port,CH376S_INT_Pin)==GPIO_PIN_RESET)	
			{
				_tmpReturn = getInterrupt(); // get int message
			}//end if int message pending
		}
		switch(_tmpReturn){ // 0x15 device attached, 0x16 device disconnect
		case ANSW_USB_INT_CONNECT:
			_deviceAttached = true;
			rdDiskInfo();
			break;
		case ANSW_USB_INT_DISCONNECT:
			_deviceAttached = false;
			memset(&_diskData, 0, sizeof(_diskData));// fill up with NULL disk data container
			break;
		}//end switch
	return _deviceAttached;
}

/////////////////Alap parancs kuldes az USB fele/////////////////
void sendCommand(uint8_t b_parancs){
	if(_interface == UART){
	write(0x57);// UART first sync command
	write(0xAB);// UART second sync command
	}//end if
	write(b_parancs);
}

/////////////////////////////////////////////////////////////////
uint8_t Ch376msc_openFile(){
	if(_interface == UART){
		sendCommand(CMD_FILE_OPEN);
		_answer = readSerDataUSB();
	} else {//spi
		spiBeginTransfer();
		sendCommand(CMD_FILE_OPEN);
		spiEndTransfer();
		_answer = spiWaitInterrupt();
	}
	if(_answer == ANSW_USB_INT_SUCCESS){ // get the file size
		dirInfoRead();
	}
	return _answer;
}

/////////////////////////////////////////////////////////////////
uint8_t dirInfoRead(){
	uint8_t _tmpReturn;
	if(_interface == UART){
		sendCommand(CMD_DIR_INFO_READ);// max 16 files 0x00 - 0x0f
		write(0xff);// current file is 0xff
		_tmpReturn = readSerDataUSB();
	} else {//spi
		spiBeginTransfer();
		sendCommand(CMD_DIR_INFO_READ);// max 16 files 0x00 - 0x0f
		write(0xff);// current file is 0xff
		spiEndTransfer();
		_tmpReturn = spiWaitInterrupt();
	}
	rdFatInfo();
	return _tmpReturn;
}

/////////////////////////////////////////////////////////////////
uint8_t Ch376msc_dirInfoSave(){
	uint8_t _tmpReturn = 0;
	_fileWrite = true;
	if(_interface == UART) {
		sendCommand(CMD_DIR_INFO_READ);
		write(0xff);// current file is 0xff
		readSerDataUSB();
		writeFatData();//send fat data
		sendCommand(CMD_DIR_INFO_SAVE);
		_tmpReturn = readSerDataUSB();
	} else {//spi
		spiBeginTransfer();
		sendCommand(CMD_DIR_INFO_READ);
		write(0xff);// current file is 0xff
		spiEndTransfer();
		getInterrupt();
		writeFatData();//send fat data
		spiBeginTransfer();
		sendCommand(CMD_DIR_INFO_SAVE);
		spiEndTransfer();
		_tmpReturn = spiWaitInterrupt();
	}
	return _tmpReturn;
}

/////////////////////////////////////////////////////////////////
void writeFatData(){// see fat info table under next filename
	uint8_t fatInfBuffer[32]; //temporary buffer for raw file FAT info
	memcpy ( &fatInfBuffer, &_fileData,  sizeof(fatInfBuffer) ); //copy raw data to temporary buffer
	if(_interface == SPII) spiBeginTransfer();
	sendCommand(CMD_WR_OFS_DATA);
	write((uint8_t)0x00);
	write(32);
	for(uint8_t d = 0;d < 32; d++){
		write(fatInfBuffer[d]);
		//address++;
	}
	if(_interface == SPII) spiEndTransfer();
}

////////////////////////////////////////////////////////////////
uint8_t Ch376msc_closeFile(){ // 0x00 - frissites nelkul, 0x01 adatmeret frissites
	uint8_t _tmpReturn = 0;
	uint8_t d = 0x00;
	if(_fileWrite){ // if closing file after write procedure
		d = 0x01; // close with 0x01 (to update file length)
	}
	if(_interface == UART){
		sendCommand(CMD_FILE_CLOSE);
		write(d);
		_tmpReturn = readSerDataUSB();
	} else {
		spiBeginTransfer();
		sendCommand(CMD_FILE_CLOSE);
		write(d);
		//read();
		spiEndTransfer();
		_tmpReturn = spiWaitInterrupt();
	}
	memset(&_fileData, 0, sizeof(_fileData));// fill up with NULL file data container
	_filename[0] = '\0'; // put  NULL char at the first place in a name string
	_fileWrite = false;
	_sectorCounter = 0;
	return _tmpReturn;
}

////////////////////////////////////////////////////////////////
uint8_t Ch376msc_deleteFile(){
	if(_interface == UART) {
		sendCommand(CMD_FILE_ERASE);
		_answer = readSerDataUSB();
	} else {
		spiBeginTransfer();
		sendCommand(CMD_FILE_ERASE);
		spiEndTransfer();
		_answer = spiWaitInterrupt();
	}
	return _answer;
}

///////////////////////////////////////////////////////////////
uint8_t fileEnumGo(){
	uint8_t _tmpReturn = 0;
	if(_interface == UART){
		sendCommand(CMD_FILE_ENUM_GO);
		_tmpReturn = readSerDataUSB();
	} else {
		spiBeginTransfer();
		sendCommand(CMD_FILE_ENUM_GO);
		spiEndTransfer();
		_tmpReturn = spiWaitInterrupt();
	}
	return _tmpReturn;
}

//////////////////////////////////////////////////////////////
uint8_t byteRdGo(){
	uint8_t _tmpReturn = 0;
	if(_interface == UART) {
		sendCommand(CMD_BYTE_RD_GO);
		_tmpReturn = readSerDataUSB();
	} else {
		spiBeginTransfer();
		sendCommand(CMD_BYTE_RD_GO);
		spiEndTransfer();
		_tmpReturn = spiWaitInterrupt();
	}
	return _tmpReturn;
}

//////////////////////////////////////////////////////////////
uint8_t fileCreate(){
	uint8_t _tmpReturn = 0;
	if(_interface == UART) {
		sendCommand(CMD_FILE_CREATE);
		_tmpReturn = readSerDataUSB();
	} else {
		spiBeginTransfer();
		sendCommand(CMD_FILE_CREATE);
		spiEndTransfer();
		_tmpReturn = spiWaitInterrupt();
	}
	return _tmpReturn;
}

////	////	////	////	////	////	////	////
///////////////////Listing files////////////////////////////
uint8_t Ch376msc_listDir(){
/* __________________________________________________________________________________________________________
 * | 00 - 07 | 08 - 0A |  	0B     |     0C    |     0D     | 0E  -  0F | 10  -  11 | 12 - 13|  14 - 15 |
 * |Filename |Extension|File attrib|User attrib|First ch del|Create time|Create date|Owner ID|Acc rights|
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * | 16 - 17 | 18 - 19 |   1A - 1B   |  1C  -  1F |
 * |Mod. time|Mod. date|Start cluster|  File size |
 *
 * https://en.wikipedia.org/wiki/Design_of_the_FAT_file_system
 * http://www.tavi.co.uk/phobos/fat.html
 */
	bool moreFiles = true;  // more files waiting for read out
	bool doneFiles = false; // done with reading a file
	while(!doneFiles){
		switch (fileProcesSTM) {
			case REQUEST:
				Ch376msc_setFileName("*");
				Ch376msc_sendFilename();
				_answer = Ch376msc_openFile();
				_fileWrite = false; // read mode, required for close procedure
				fileProcesSTM = READWRITE;
				break;
			case READWRITE:
				if(_answer == ANSW_ERR_MISS_FILE){
					fileProcesSTM =DONE;
					moreFiles = false;// no more files in the directory
				}//end if
				if(_answer == ANSW_USB_INT_DISK_READ){
					rdFatInfo(); // read data to fatInfo buffer
					fileProcesSTM = NEXT;
				}
				break;
			case NEXT:
				_answer = fileEnumGo(); // go for the next filename
				fileProcesSTM = DONE;
				break;
			case DONE:
				if(!moreFiles){
					Ch376msc_closeFile(); // if no more files in the directory, close the file
					fileProcesSTM = REQUEST;
				} else {
					fileProcesSTM = READWRITE;
				}

				doneFiles = true;
				break;
		}// end switch
	}//end while
	return moreFiles;
}

////////////////////////////  Read  cycle//////////////////////////
uint8_t Ch376msc_readFile(char* buffer, uint8_t b_num){ //buffer for reading, buffer size
	uint8_t _tmpReturn = 0;// more data
	uint8_t byteForRequest ;
	bool bufferFull = false;
	_fileWrite = false; // read mode, required for close procedure
	b_num--;// last byte is reserved for NULL terminating character
	if(_answer == ANSW_ERR_FILE_CLOSE || _answer == ANSW_ERR_MISS_FILE){
		bufferFull = true;
		_tmpReturn = 0;// we have reached the EOF
	}
	while(!bufferFull){

		switch (fileProcesSTM) {
			case REQUEST:
				byteForRequest = b_num - _byteCounter;
				if(_sectorCounter == SECTORSIZE){ //if one sector has read out
					_sectorCounter = 0;
					fileProcesSTM = NEXT;
					break;
				} else if((_sectorCounter + byteForRequest) > SECTORSIZE){
					byteForRequest = SECTORSIZE - _sectorCounter;
				}
				////////////////
				_answer = reqByteRead(byteForRequest);
				if(_answer == ANSW_USB_INT_DISK_READ){
					fileProcesSTM = READWRITE;
					_tmpReturn = 1; //we have not reached the EOF
				} else if(_answer == ANSW_USB_INT_SUCCESS){ // no more data, EOF
					fileProcesSTM = DONE;
					_tmpReturn = 0;
				}
				break;
			case READWRITE:
				_sectorCounter += readDataToBuff(buffer);	//fillup the buffer
				if(_byteCounter != b_num) {
					fileProcesSTM = REQUEST;
				} else {
					fileProcesSTM = DONE;
				}
				break;
			case NEXT:
				_answer = byteRdGo();
				fileProcesSTM = REQUEST;
				break;
			case DONE:
				fileProcesSTM = REQUEST;
				buffer[_byteCounter] = '\0';// NULL terminating char
				_byteCounter = 0;
				bufferFull = true;
				break;
		}//end switch
	}//end while
		return _tmpReturn;
}

///////////////////////////Write cycle/////////////////////////////

uint8_t Ch376msc_writeFile(char* buffer, uint8_t b_num){
	_fileWrite = true; // read mode, required for close procedure
	_byteCounter = 0;
	bool diskFree = true; //free space on a disk
	bool bufferFull = true; //continue to write while there is data in the temporary buffer
	if(_diskData.freeSector == 0){
		diskFree = false;
		return diskFree;
	}
	if(_answer == ANSW_ERR_MISS_FILE){ // no file with given name
		_answer = fileCreate();
	}//end if CREATED

	if(_answer == ANSW_ERR_FILE_CLOSE){
		_answer = Ch376msc_openFile();
	}

	if(_answer == ANSW_USB_INT_SUCCESS){ // file created succesfully

		while(bufferFull){
			switch (fileProcesSTM) {
				case REQUEST:
					_answer = reqByteWrite(b_num - _byteCounter);

					if(_answer == ANSW_USB_INT_SUCCESS){
						fileProcesSTM = NEXT;

					} else if(_answer == ANSW_USB_INT_DISK_WRITE){
						fileProcesSTM = READWRITE;
						}
					break;
				case READWRITE:
					writeDataFromBuff(buffer);
					if(_byteCounter != b_num) {
						fileProcesSTM = NEXT;
					} else {
						fileProcesSTM = DONE;
					}
					break;
				case NEXT:
					if(_diskData.freeSector > 0){
						_diskData.freeSector --;
						_answer = byteWrGo();
						if(_answer == ANSW_USB_INT_SUCCESS){
							fileProcesSTM = REQUEST;
						} else if(_byteCounter != b_num ){
							fileProcesSTM = READWRITE;
						}
					} else { // if disk is full
						fileProcesSTM = DONE;
						diskFree = false;
					}
					break;
				case DONE:
					fileProcesSTM = REQUEST;
					_byteCounter = 0;
					_answer = byteWrGo();
					bufferFull = false;
					break;
			}//end switch
		}//end while
	}// end file created

	return diskFree;
}

/////////////////////////////////////////////////////////////////
void rdFatInfo(){
	uint8_t fatInfBuffer[32]; //temporary buffer for raw file FAT info
	uint8_t dataLength;
	if(_interface == UART){
		sendCommand(CMD_RD_USB_DATA0);
		dataLength = readSerDataUSB();
		for(uint8_t s =0;s < dataLength;s++){
			fatInfBuffer[s] = readSerDataUSB();// fill up temporary buffer
		}//end for
	} else {
		spiBeginTransfer();
		sendCommand(CMD_RD_USB_DATA0);
		dataLength = spiReadData();
		for(uint8_t s =0;s < dataLength;s++){
			fatInfBuffer[s] = spiReadData();// fill up temporary buffer
		}//end for
		spiEndTransfer();
	}
	memcpy ( &_fileData, &fatInfBuffer, sizeof(fatInfBuffer) ); //copy raw data to structured variable
}

/////////////////////////////////////////////////////////////////
uint8_t byteWrGo(){
	uint8_t _tmpReturn = 0;
	if(_interface == UART) {
		sendCommand(CMD_BYTE_WR_GO);
		_tmpReturn = readSerDataUSB();
	} else {
		spiBeginTransfer();
		sendCommand(CMD_BYTE_WR_GO);
		spiEndTransfer();
		_tmpReturn = spiWaitInterrupt();
	}
	return _tmpReturn;
}

/////////////////////////////////////////////////////////////////
uint8_t readDataToBuff(char* buffer){
	uint8_t oldCounter = _byteCounter; //old buffer counter
	uint8_t dataLength; // data stream size
	if(_interface == UART) {
		sendCommand(CMD_RD_USB_DATA0);
		dataLength = readSerDataUSB(); // data stream size
		while(_byteCounter < (dataLength + oldCounter)){
			buffer[_byteCounter]=readSerDataUSB(); // incoming data add to buffer
			_byteCounter ++;
		}//end while
	} else {
	spiBeginTransfer();
	sendCommand(CMD_RD_USB_DATA0);
	dataLength = spiReadData(); // data stream size
	while(_byteCounter < (dataLength + oldCounter)){
		buffer[_byteCounter]=spiReadData(); // incoming data add to buffer
		_byteCounter ++;
	}//end while
	spiEndTransfer();
	}
	return dataLength;
}

/////////////////////////////////////////////////////////////////
uint8_t writeDataFromBuff(char* buffer){//====================
	uint8_t oldCounter = _byteCounter; //old buffer counter
	uint8_t dataLength; // data stream size
	if(_interface == UART) {
		sendCommand(CMD_WR_REQ_DATA);
		dataLength = readSerDataUSB(); // data stream size
	} else {
		spiBeginTransfer();
		sendCommand(CMD_WR_REQ_DATA);
		dataLength = spiReadData(); // data stream size
	}
	while(_byteCounter < (dataLength + oldCounter)){
		write(buffer[_byteCounter]); // read data from buffer and write to serial port
		_byteCounter ++;
	}//end while
	if(_interface == SPII) spiEndTransfer();
	return dataLength;
}

/////////////////////////////////////////////////////////////////
uint8_t reqByteRead(uint8_t a){
	uint8_t tmpReturn = 0;
	if(_interface == UART){
		sendCommand(CMD_BYTE_READ);
		write(a); // request data stream length for reading, 00 - FF
		write((uint8_t)0x00);
		tmpReturn= readSerDataUSB();
	} else {
		spiBeginTransfer();
		sendCommand(CMD_BYTE_READ);
		write(a); // request data stream length for reading, 00 - FF
		write((uint8_t)0x00);
		spiEndTransfer();
		tmpReturn= spiWaitInterrupt();
	}
	return tmpReturn;
}

////////////////////////////////////////////////////////////////
uint8_t reqByteWrite(uint8_t a){
	uint8_t tmpReturn = 0;
	if(_interface == UART) {
		sendCommand(CMD_BYTE_WRITE);
		write(a); // request data stream length for writing, 00 - FF
		write((uint8_t)0x00);
		tmpReturn = readSerDataUSB();
	} else {
		spiBeginTransfer();
		sendCommand(CMD_BYTE_WRITE);
		write(a); // request data stream length for writing, 00 - FF
		write((uint8_t)0x00);
		spiEndTransfer();
		tmpReturn = spiWaitInterrupt();
	}
	return tmpReturn;
}

/////////////////////////////////////////////////////////////////
uint8_t Ch376msc_moveCursor(uint32_t position){
	uint8_t tmpReturn = 0;
	fSizeContainer cPosition; //unsigned long union
	if(position > _fileData.size){	//fix for moveCursor issue #3 Sep 17, 2019
		_sectorCounter = _fileData.size % SECTORSIZE;
	} else {
		_sectorCounter = position % SECTORSIZE;
	}
	cPosition.value = position;
	if(_interface == SPII) spiBeginTransfer();
	sendCommand(CMD_BYTE_LOCATE);
	write(cPosition.b[0]);
	write(cPosition.b[1]);
	write(cPosition.b[2]);
	write(cPosition.b[3]);
	if(_interface == UART){
		tmpReturn = readSerDataUSB();
	} else {
		spiEndTransfer();
		tmpReturn = spiWaitInterrupt();
	}
	return tmpReturn;
}

/////////////////////////////////////////////////////////////////
void Ch376msc_sendFilename(){
	if(_interface == SPII) spiBeginTransfer();
	sendCommand(CMD_SET_FILE_NAME);
	write(0x2f); // "/" root directory
	print(_filename); // filename
	write(0x5C);	// ez a "\" jel
	write((uint8_t)0x00);	// ez a lezaro 0 jel
	if(_interface == SPII) spiEndTransfer();
}
/////////////////////////////////////////////////////////////////
void rdDiskInfo(){
	uint8_t dataLength;
	uint8_t tmpReturn;
	uint8_t tmpdata[9];
	if(_interface == UART){
		sendCommand(CMD_DISK_QUERY);
		tmpReturn= readSerDataUSB();
		if(tmpReturn == ANSW_USB_INT_SUCCESS){
			sendCommand(CMD_RD_USB_DATA0);
			dataLength = readSerDataUSB();
			for(uint8_t s =0;s < dataLength;s++){
				tmpdata[s] = readSerDataUSB();// fill up temporary buffer
			}//end for
		}//end if success
	} else {
		spiBeginTransfer();
		sendCommand(CMD_DISK_QUERY);
		spiEndTransfer();
		tmpReturn= spiWaitInterrupt();
		if(tmpReturn == ANSW_USB_INT_SUCCESS){
			spiBeginTransfer();
			sendCommand(CMD_RD_USB_DATA0);
			dataLength = spiReadData();
			for(uint8_t s =0;s < dataLength;s++){
				tmpdata[s] = spiReadData();// fill up temporary buffer
			}//end for
			spiEndTransfer();
		}//end if success
	}//end if UART
	memcpy ( &_diskData, &tmpdata, sizeof(tmpdata) ); //copy raw data to structured variable
}
