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
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "usb_device.h"
#include "usbd_hid.h"
#include "hid_keyboard.h"



extern USBD_HandleTypeDef hUsbDeviceFS;


int  SendKeyBoardChar(uint8_t ch)
{
	int send=0;
	
	struct HIDkeyboardReport_t 
	{
      uint8_t id;
      uint8_t modifiers;
      uint8_t key1;
      uint8_t key2;
      uint8_t key3;
			
	};
	struct HIDkeyboardReport_t HIDkeyboardReport;
	
	HIDkeyboardReport.id = 1;
	HIDkeyboardReport.modifiers = 0;
	HIDkeyboardReport.key1 = 0;
	HIDkeyboardReport.key2 = 0;
	HIDkeyboardReport.key3 = 0;
	
	
	//Capital letters
		if (ch >= 0x41 && ch <= 0x5A) {
			HIDkeyboardReport.key1 = KB_A + (ch - 0x41);
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}
		//lower case letters
		else if (ch >= 0x61 && ch <= 0x7A) {
			HIDkeyboardReport.key1 = KB_A + (ch - 0x61);
			HIDkeyboardReport.modifiers = 0;
			send = 1;
		}
		//Enter
		else if (ch == 0x0D) {
			HIDkeyboardReport.key1 = KB_ENTER;
			HIDkeyboardReport.modifiers = 0;
			send = 1;
		}
//		//\r 
//		else if (ch == 0x0A) {
//			HIDkeyboardReport.key1 = KB_;
//			HIDkeyboardReport.modifiers = 0;
//			send = 1;
//		}
		//Space
		else if (ch == 0x20) {
			HIDkeyboardReport.key1 = KB_SPACEBAR;
			HIDkeyboardReport.modifiers = 0;
			send = 1;
		}
		//Numbers 1-9
		else if (ch >= 0x31 && ch <= 0x39) {
			HIDkeyboardReport.key1 = KB_1 + (ch - 0x31);
			HIDkeyboardReport.modifiers = 0;
			send = 1;
		}
		//Number 0
		else if (ch == 0x30) {
			HIDkeyboardReport.key1 = KB_0;
			HIDkeyboardReport.modifiers = 0;
			send = 1;
		}
		//!
		else if (ch == ASCII_EXCLAMATION) {
			HIDkeyboardReport.key1 = KB_1;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}
		//@
		else if (ch == ASCII_AT) {
			HIDkeyboardReport.key1 = KB_2;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}
		//#
		else if (ch == ASCII_POUND) {
			HIDkeyboardReport.key1 = KB_3;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}
		//$
		else if (ch == ASCII_DOLLAR) {
			HIDkeyboardReport.key1 = KB_4;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}

		//%
		else if (ch == ASCII_PERCENTAGE) {
			HIDkeyboardReport.key1 = KB_5;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}
		//^
		else if (ch == ASCII_CARET) {
			HIDkeyboardReport.key1 = KB_6;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}
		//&
		else if (ch == ASCII_AND) {
			HIDkeyboardReport.key1 = KB_7;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}
		//*
		else if (ch == ASCII_STAR) {
			HIDkeyboardReport.key1 = KB_8;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}
		//(
		else if (ch == ASCII_LEFT_PARENTH) {
			HIDkeyboardReport.key1 = KB_9;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}
		//)
		else if (ch == ASCII_RIGHT_PARENTH) {
			HIDkeyboardReport.key1 = KB_0;
			HIDkeyboardReport.modifiers = 0x02;
			send = 1;
		}

		//`
		else if (ch == ASCII_ACUTE) {
					HIDkeyboardReport.key1 = KB_ACUTE;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		//~
		else if (ch == ASCII_TILDE) {
					HIDkeyboardReport.key1 = KB_ACUTE;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//{
		else if (ch == ASCII_OPEN_BRACE) {
					HIDkeyboardReport.key1 = KB_OPEN_BRACKET;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//[
		else if (ch == ASCII_OPEN_BRACKET) {
					HIDkeyboardReport.key1 = KB_OPEN_BRACKET;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		//}
		else if (ch == ASCII_CLOSE_BRACE) {
					HIDkeyboardReport.key1 = KB_CLOSE_BRACKET;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//]
		else if (ch == ASCII_CLOSE_BRACKET) {
					HIDkeyboardReport.key1 = KB_CLOSE_BRACKET;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		// \

		else if (ch == ASCII_BACKSLASH) {
					HIDkeyboardReport.key1 = KB_BACKSLASH;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		//|
		else if (ch == ASCII_PIPE) {
					HIDkeyboardReport.key1 = KB_BACKSLASH;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//:
		else if (ch == ASCII_COLON) {
					HIDkeyboardReport.key1 = KB_SEMICOLON;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//;
		else if (ch == ASCII_SEMICOLON) {
					HIDkeyboardReport.key1 = KB_SEMICOLON;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		//"
		else if (ch == ASCII_QUOTE) {
					HIDkeyboardReport.key1 = KB_QUOTE;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//'
		else if (ch == ASCII_APOSTROPHE) {
					HIDkeyboardReport.key1 = KB_QUOTE;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		//<
		else if (ch == ASCII_LESS_THAN) {
					HIDkeyboardReport.key1 = KB_LESS_THAN;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//,
		else if (ch == ASCII_COMMA) {
					HIDkeyboardReport.key1 = KB_LESS_THAN;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		//>
		else if (ch == ASCII_GREATER_THAN) {
					HIDkeyboardReport.key1 = KB_GREATER_THAN;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//.
		else if (ch == ASCII_PERIOD) {
					HIDkeyboardReport.key1 = KB_GREATER_THAN;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		//?
		else if (ch == ASCII_QUESTION_MARK) {
					HIDkeyboardReport.key1 = KB_FORWARD_SLASH;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		///
		else if (ch == ASCII_FORWARD_SLASH) {
					HIDkeyboardReport.key1 = KB_FORWARD_SLASH;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		//-
		else if (ch == ASCII_DASH) {
					HIDkeyboardReport.key1 = KB_DASH;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}
		//_
		else if (ch == ASCII_UNDERSCORE) {
					HIDkeyboardReport.key1 = KB_DASH;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//+
		else if (ch == ASCII_PLUS){
					HIDkeyboardReport.key1 = KB_EQUALS;
					HIDkeyboardReport.modifiers = 0x02;
					send = 1;
				}
		//=
		else if (ch == ASCII_EQUALS) {
					HIDkeyboardReport.key1 = KB_EQUALS;
					HIDkeyboardReport.modifiers = 0x00;
					send = 1;
				}

//		//Up arrow
//#ifdef OSX
//		else if (ch == 0xe2 && receivedData[1] == 0x88
//				&& receivedData[2] == 0x91) {

//#else
//		else if (ch == 0x1b && receivedData[1] == ASCII_w) {
//#endif
//			HIDkeyboardReport.key1 = KB_UP;
//			HIDkeyboardReport.modifiers = 0;
//			send = 1;
//		}

//		//Left arrow
//#ifdef OSX
//		else if (ch == 0xc3 && receivedData[1] == 0xa5) {

//#else
//		else if (ch == 0x1b && receivedData[1] == ASCII_a) {
//#endif
//			HIDkeyboardReport.key1 = KB_LEFT;
//			HIDkeyboardReport.modifiers = 0;
//			send = 1;
//		}
//		//Down arrow

//#ifdef OSX
//		else if (ch == 0xc3 && receivedData[1] == 0x9f) {

//#else
//		else if (ch == 0x1b && receivedData[1] == ASCII_s) {

//#endif
//			HIDkeyboardReport.key1 = KB_DOWN;
//			HIDkeyboardReport.modifiers = 0;
//			send = 1;
//		}
//		//right arrow

//#ifdef OSX
//		else if (ch == 0xe2 && receivedData[1] == 0x88
//				&& receivedData[2] == 0x82) {

//#else
//		else if (ch == 0x1b && receivedData[1] == ASCII_d) {

//#endif
//			HIDkeyboardReport.key1 = KB_RIGHT;
//			HIDkeyboardReport.modifiers = 0;
//			send = 1;
//		}
//		//Backspace
//#ifdef OSX
//		else if (ch == 0xc5 && receivedData[1] == 0x93) {
//#else
//		else if (ch == 0x1b && receivedData[1] == ASCII_q) {
//#endif

//			HIDkeyboardReport.key1 = KB_BACKSPC;
//			HIDkeyboardReport.modifiers = 0;
//			send = 1;
//		}

//#ifdef OSX
//		//TODO: Add delete for OSX
//#else
//		else if (ch == 0x1b && receivedData[1] == ASCII_e) {
//#endif
//			HIDkeyboardReport.key1 = KB_DELETE;
//			HIDkeyboardReport.modifiers = 0;
//			send = 1;
//		}
//#ifdef wat
//		if (ch != 0) {
//			HIDkeyboardReport.key1 = 0;
//			HIDkeyboardReport.modifiers = 0;
//			send = 1;

//		}
//#endif

		//Only send report if a key has been pressed
		if (send == 1) 
		{
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDkeyboardReport,sizeof(struct HIDkeyboardReport_t));
			HAL_Delay(30);
			HIDkeyboardReport.key1 = 0;
			HIDkeyboardReport.modifiers = 0;
			USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&HIDkeyboardReport,sizeof(struct HIDkeyboardReport_t));
			HAL_Delay(10);
			send = 0;
		}


		return send;
	}

