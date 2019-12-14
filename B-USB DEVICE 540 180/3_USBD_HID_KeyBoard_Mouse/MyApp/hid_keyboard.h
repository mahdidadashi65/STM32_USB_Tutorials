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


#ifndef HID_KEYBOARD_H_
#define HID_KEYBOARD_H_


#include "main.h"


#ifdef __cplusplus
extern "C" {
#endif
	

int  SendKeyBoardChar(uint8_t ch);



// USB media codes
#define USB_HID_SCAN_NEXT 0x01
#define USB_HID_SCAN_PREV 0x02
#define USB_HID_STOP      0x04
#define USB_HID_EJECT     0x08
#define USB_HID_PAUSE     0x10
#define USB_HID_MUTE      0x20
#define USB_HID_VOL_UP    0x40
#define USB_HID_VOL_DEC   0x80

// USB keyboard codes
#define USB_HID_MODIFIER_NONE   0x00
#define USB_HID_MODIFIER_LEFT_CTRL   0x01
#define USB_HID_MODIFIER_LEFT_SHIFT  0x02
#define USB_HID_MODIFIER_LEFT_ALT    0x04
#define USB_HID_MODIFIER_LEFT_GUI    0x08 // (Win/Apple/Meta)
#define USB_HID_MODIFIER_RIGHT_CTRL  0x10
#define USB_HID_MODIFIER_RIGHT_SHIFT 0x20
#define USB_HID_MODIFIER_RIGHT_ALT   0x40
#define USB_HID_MODIFIER_RIGHT_GUI   0x80

#define KB_NONE 0x00
#define KB_A 0x04
#define KB_B 0x05
#define KB_C 0x06
#define KB_D 0x07
#define KB_E 0x08
#define KB_F 0x09
#define KB_G 0x0A
#define KB_H 0x0B
#define KB_I 0x0C
#define KB_J 0x0D
#define KB_K 0x0E
#define KB_L 0x0F
#define KB_M 0x10
#define KB_N 0x11
#define KB_O 0x12
#define KB_P 0x13
#define KB_Q 0x14
#define KB_R 0x15
#define KB_S 0x16
#define KB_T 0x17
#define KB_U 0x18
#define KB_V 0x19
#define KB_W 0x1A
#define KB_X 0x1B
#define KB_Y 0x1C
#define KB_Z 0x1D

#define KB_1 0x1E
#define KB_2 0X1F
#define KB_3 0x20
#define KB_4 0x21
#define KB_5 0x22
#define KB_6 0x23
#define KB_7 0x24
#define KB_8 0x25
#define KB_9 0x26
#define KB_0 0x27

#define KB_ENTER 0x28
#define KB_ESCAPE 0x29
#define KB_BACKSPC 0x2A
#define KB_TAB 0x2B
#define KB_SPACEBAR 0x2C
#define KB_DASH 0x2D
#define KB_EQUALS 0x2C
#define KN_LEFT_BRACKET 0x2D
#define KB_DELETE 0x4C	//Keyboard Delete Forward

#define KB_ACUTE 0x35
#define KB_OPEN_BRACKET 0x2F
#define KB_CLOSE_BRACKET 0x30
#define KB_BACKSLASH 0x31
#define KB_SEMICOLON 0x33
#define KB_QUOTE 0x34
#define KB_LESS_THAN 0x36
#define KB_GREATER_THAN 0x37
#define KB_FORWARD_SLASH 0x38

#define KB_UP 0x52
#define KB_LEFT 0x50
#define KB_DOWN 0x51
#define KB_RIGHT 0x4F

#define ASCII_q 0x71
#define ASCII_w 0x77
#define ASCII_a 0x61
#define ASCII_s 0x73
#define ASCII_d 0x64
#define ASCII_e 0x65


//Top row  number shift
#define ASCII_EXCLAMATION 0x21
#define ASCII_AT 0x40
#define ASCII_POUND 0x23
#define ASCII_DOLLAR 0x24
#define ASCII_PERCENTAGE 0x25
#define ASCII_CARET 0x5E
#define ASCII_AND 0x26
#define ASCII_STAR 0x2A
#define ASCII_LEFT_PARENTH 0x28
#define ASCII_RIGHT_PARENTH 0x29
#define ASCII_UNDERSCORE 0x5F
#define ASCII_PLUS 0x2B

#define ASCII_EQUALS 0x3D

#define ASCII_DASH 0x2D
#define ASCII_PLUS 0x2B

#define ASCII_ACUTE 0x60
#define ASCII_TILDE 0x7E
#define ASCII_OPEN_BRACE 0x7B
#define ASCII_CLOSE_BRACE 0x7D
#define ASCII_OPEN_BRACKET 0x5B
#define ASCII_CLOSE_BRACKET 0x5D
#define ASCII_PIPE 0x7C
#define ASCII_BACKSLASH 0x5C
#define ASCII_COLON 0x3A
#define ASCII_SEMICOLON 0x3B
#define ASCII_QUOTE 0x22
#define ASCII_APOSTROPHE 0x27
#define ASCII_LESS_THAN 0x3C
#define ASCII_GREATER_THAN 0x3E
#define ASCII_COMMA 0x2C
#define ASCII_PERIOD 0x2E
#define ASCII_QUESTION_MARK 0x3F
#define ASCII_FORWARD_SLASH 0x2F


#if defined(__cplusplus)
}
#endif

#endif /* HID_KEYBOARD_H_ */
