/*
 * comm.cpp
 *
 *  Created on: Apr 6, 2019
 *      Author: György Kovács
 */




#include "Ch376msc.h"



extern SPI_HandleTypeDef hspi3;

void delayMicroseconds(int us)
{
	HAL_Delay(us);
}

int millis(void)
{
	return HAL_GetTick();
}


uint8_t Ch376msc::readSerDataUSB(){
//	uint32_t oldMillis = millis();
//		while (!_comPort->available()){ // wait until data is arrive
//			if ((millis()- oldMillis) > TIMEOUT){
//				return 0xFF; // Timeout valasz
//			}//end if
//		}//end while
//	return _comPort->read();
}

void Ch376msc::write(uint8_t data){
	if(_interface == UART){
		//_comPort->write(data);
	} else { // SPI
		delayMicroseconds(3);//datasheet TSC min 1.5uSec
		spiReady();
		
		HAL_SPI_Transmit(&hspi3,&data,1,100);
		//	SPI.transfer(data);
		}
	}//end SPI

uint8_t Ch376msc::spiReadData(){
	
	uint8_t DataOut,DataIn;
	delayMicroseconds(3);//datasheet TSC min 1.5uSec
	spiReady();
	
	DataOut=0;
	HAL_SPI_TransmitReceive(&hspi3,&DataOut,&DataIn,1,100);
	//return SPI.transfer(0x00);
	return DataIn;
}
void Ch376msc::print(const char str[]){
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

void Ch376msc::spiReady(){
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

uint8_t Ch376msc::spiWaitInterrupt(){
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

uint8_t Ch376msc::getInterrupt(){
	uint8_t _tmpReturn = 0;
	//spiWaitInterrupt();
		spiBeginTransfer();
		sendCommand(CMD_GET_STATUS);
		_tmpReturn = spiReadData();
		spiEndTransfer();
	return _tmpReturn;
}

void Ch376msc::spiBeginTransfer(){
	spiReady();
//	SPI.beginTransaction(SPISettings(SPICLKRATE, MSBFIRST, SPI_MODE0));
//	digitalWrite(_spiChipSelect, LOW);
	
	HAL_GPIO_WritePin(CH376S_CS_GPIO_Port,CH376S_CS_Pin,GPIO_PIN_RESET);
	
}

void Ch376msc::spiEndTransfer(){
//	digitalWrite(_spiChipSelect, HIGH);
//	SPI.endTransaction();
	
	HAL_GPIO_WritePin(CH376S_CS_GPIO_Port,CH376S_CS_Pin,GPIO_PIN_SET);
}
