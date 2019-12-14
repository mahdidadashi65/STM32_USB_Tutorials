/* USER CODE BEGIN Header */


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


 /* USER CODE END Header */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_DISKIO_H
#define __USER_DISKIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* USER CODE BEGIN 0 */
#include "ff_gen_drv.h"
//#include "mymain.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
#define MySDSPI  hspi1
#define MySD_SEL HAL_GPIO_WritePin(uSD_CS_GPIO_Port, uSD_CS_Pin, GPIO_PIN_RESET)
#define MySD_DESEL HAL_GPIO_WritePin(uSD_CS_GPIO_Port, uSD_CS_Pin, GPIO_PIN_SET);


/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern Diskio_drvTypeDef  USER_Driver;

/* USER CODE END 0 */
   
#ifdef __cplusplus
}
#endif

#endif /* __USER_DISKIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
