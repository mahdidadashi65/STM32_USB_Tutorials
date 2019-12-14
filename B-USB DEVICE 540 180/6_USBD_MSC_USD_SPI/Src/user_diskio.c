/* USER CODE BEGIN Header */

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


 /* USER CODE END Header */

#ifdef USE_OBSOLETE_USER_CODE_SECTION_0
/* 
 * Warning: the user section 0 is no more in use (starting from CubeMx version 4.16.0)
 * To be suppressed in the future. 
 * Kept to ensure backward compatibility with previous CubeMx versions when 
 * migrating projects. 
 * User code previously added there should be copied in the new user sections before 
 * the section contents can be deleted.
 */
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */
#endif

/* USER CODE BEGIN DECL */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "ff_gen_drv.h"
#include "user_diskio.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#include <stdbool.h>
/* Private variables ---------------------------------------------------------*/
/* Disk status */
//static volatile DSTATUS Stat = STA_NOINIT;


/* Definitions for MMC/SDC command */
#define CMD0    (0x40+0)    /* GO_IDLE_STATE */
#define CMD1    (0x40+1)    /* SEND_OP_COND */
#define CMD8    (0x40+8)    /* SEND_IF_COND */
#define CMD9    (0x40+9)    /* SEND_CSD */
#define CMD10    (0x40+10)    /* SEND_CID */
#define CMD12    (0x40+12)    /* STOP_TRANSMISSION */
#define CMD16    (0x40+16)    /* SET_BLOCKLEN */
#define CMD17    (0x40+17)    /* READ_SINGLE_BLOCK */
#define CMD18    (0x40+18)    /* READ_MULTIPLE_BLOCK */
#define CMD23    (0x40+23)    /* SET_BLOCK_COUNT */
#define CMD24    (0x40+24)    /* WRITE_BLOCK */
#define CMD25    (0x40+25)    /* WRITE_MULTIPLE_BLOCK */
#define CMD41    (0x40+41)    /* SEND_OP_COND (ACMD) */
#define CMD55    (0x40+55)    /* APP_CMD */
#define CMD58    (0x40+58)    /* READ_OCR */

/*--------------------------------------------------------------------------

 Module Private Functions

 ---------------------------------------------------------------------------*/

static volatile DSTATUS Stat = STA_NOINIT; /* Disk status */

static volatile BYTE Timer1, Timer2; /* 100Hz decrement timer */

static BYTE CardType; /* b0:MMC, b1:SDC, b2:Block addressing */

static BYTE PowerFlag = 0; /* indicates if "power" is on */


static
void xmit_spi(BYTE Data)
{
	while (HAL_SPI_GetState(&MySDSPI) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&MySDSPI, &Data, 1, 5000);
}

static BYTE rcvr_spi(void)
{
	unsigned char Dummy, Data;
	Dummy = 0xFF;
	Data = 0;
	while ((HAL_SPI_GetState(&MySDSPI) != HAL_SPI_STATE_READY))
		;
	HAL_SPI_TransmitReceive(&MySDSPI, &Dummy, &Data, 1, 5000);

	return Data;
}

static
void rcvr_spi_m(BYTE *dst) {
	*dst = rcvr_spi();
}

/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------z------------------------------------------*/

static BYTE wait_ready(void) {
	BYTE res;

	Timer2 = 50;
	rcvr_spi();
	do
		res = rcvr_spi();
	while ((res != 0xFF) && Timer2);

	return res;
}

/*-----------------------------------------------------------------------*/
/* Power Control  (Platform dependent)                                   */
/*-----------------------------------------------------------------------*/
/* When the target system does not support socket power control, there   */
/* is nothing to do in these functions and chk_power always returns 1.   */

static
void power_on(void) {
	unsigned char i, cmd_arg[6];
	unsigned int Count = 0x1FFF;

	MySD_DESEL;

	for (i = 0; i < 10; i++)
		xmit_spi(0xFF);
	
	MySD_SEL;

	cmd_arg[0] = (CMD0 | 0x40);
	cmd_arg[1] = 0;
	cmd_arg[2] = 0;
	cmd_arg[3] = 0;
	cmd_arg[4] = 0;
	cmd_arg[5] = 0x95;

	for (i = 0; i < 6; i++)
		xmit_spi(cmd_arg[i]);

	while ((rcvr_spi() != 0x01) && Count)
		Count--;

	MySD_DESEL;
	xmit_spi(0XFF);

	PowerFlag = 1;
}

static
void power_off(void) {
	PowerFlag = 0;
}

static
int chk_power(void) /* Socket power state: 0=off, 1=on */
{
	return PowerFlag;
}

/*-----------------------------------------------------------------------*/
/* Receive a data packet from MMC                                        */
/*-----------------------------------------------------------------------*/

static bool rcvr_datablock(BYTE *buff, /* Data buffer to store received data */
UINT btr /* Byte count (must be even number) */
) {
	BYTE token;

	Timer1 = 10;
	do { /* Wait for data packet in timeout of 100ms */
		token = rcvr_spi();
	} while ((token == 0xFF) && Timer1);
	if (token != 0xFE)
		return false; /* If not valid data token, retutn with error */

	do { /* Receive the data block into buffer */
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
	} while (btr -= 2);
	rcvr_spi(); /* Discard CRC */
	rcvr_spi();

	return true; /* Return with success */
}

/*-----------------------------------------------------------------------*/
/* Send a data packet to MMC                                             */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
static bool xmit_datablock(const BYTE *buff, /* 512 byte data block to be transmitted */
BYTE token /* Data/Stop token */
) {
	BYTE resp, wc;
	uint32_t i = 0;

	if (wait_ready() != 0xFF)
		return false;

	xmit_spi(token); /* Xmit data token */
	if (token != 0xFD) { /* Is data token */
		wc = 0;
		do { /* Xmit the 512 byte data block to MMC */
			xmit_spi(*buff++);
			xmit_spi(*buff++);
		} while (--wc);

		rcvr_spi();
		rcvr_spi();

		while (i <= 64) {
			resp = rcvr_spi(); /* Reveive data response */
			if ((resp & 0x1F) == 0x05) /* If not accepted, return with error */
				break;
			i++;
		}
		while (rcvr_spi() == 0)
			;
	}
	if ((resp & 0x1F) == 0x05)
		return true;
	else
		return false;
}
#endif /* _READONLY */

/*-----------------------------------------------------------------------*/
/* Send a command packet to MMC                                          */
/*-----------------------------------------------------------------------*/

static BYTE send_cmd(BYTE cmd, /* Command byte */
DWORD arg /* Argument */
) {
	BYTE n, res;

	if (wait_ready() != 0xFF)
		return 0xFF;

	/* Send command packet */
	xmit_spi(cmd); /* Command */
	xmit_spi((BYTE) (arg >> 24)); /* Argument[31..24] */
	xmit_spi((BYTE) (arg >> 16)); /* Argument[23..16] */
	xmit_spi((BYTE) (arg >> 8)); /* Argument[15..8] */
	xmit_spi((BYTE) arg); /* Argument[7..0] */
	n = 0;
	if (cmd == CMD0)
		n = 0x95; /* CRC for CMD0(0) */
	if (cmd == CMD8)
		n = 0x87; /* CRC for CMD8(0x1AA) */
	xmit_spi(n);

	/* Receive command response */
	if (cmd == CMD12)
		rcvr_spi(); /* Skip a stuff byte when stop reading */
	n = 10; /* Wait for a valid response in timeout of 10 attempts */
	do
		res = rcvr_spi();
	while ((res & 0x80) && --n);

	return res; /* Return with the response value */
}
/* USER CODE END DECL */

/* Private function prototypes -----------------------------------------------*/
DSTATUS USER_initialize (BYTE pdrv);
DSTATUS USER_status (BYTE pdrv);
DRESULT USER_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
  DRESULT USER_write (BYTE pdrv, const BYTE *buff, DWORD sector, UINT count);  
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
  DRESULT USER_ioctl (BYTE pdrv, BYTE cmd, void *buff);
#endif /* _USE_IOCTL == 1 */

Diskio_drvTypeDef  USER_Driver =
{
  USER_initialize,
  USER_status,
  USER_read, 
#if  _USE_WRITE
  USER_write,
#endif  /* _USE_WRITE == 1 */  
#if  _USE_IOCTL == 1
  USER_ioctl,
#endif /* _USE_IOCTL == 1 */
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes a Drive
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS USER_initialize (
	BYTE pdrv           /* Physical drive nmuber to identify the drive */
)
{
  /* USER CODE BEGIN INIT */
    BYTE n, ty, ocr[4];

	if (pdrv)
		return STA_NOINIT; /* Supports only single drive */
	if (Stat & STA_NODISK)
		return Stat; /* No card in the socket */

	power_on(); /* Force socket power on */
	//send_initial_clock_train();

	MySD_SEL; /* CS = L */
	ty = 0;
	if (send_cmd(CMD0, 0) == 1) { /* Enter Idle state */
		Timer1 = 100; /* Initialization timeout of 1000 msec */
		if (send_cmd(CMD8, 0x1AA) == 1) { /* SDC Ver2+ */
			for (n = 0; n < 4; n++)
				ocr[n] = rcvr_spi();
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) { /* The card can work at vdd range of 2.7-3.6V */
				do {
					if (send_cmd(CMD55, 0) <= 1
							&& send_cmd(CMD41, 1UL << 30) == 0)
						break; /* ACMD41 with HCS bit */
				} while (Timer1);
				if (Timer1 && send_cmd(CMD58, 0) == 0) { /* Check CCS bit */
					for (n = 0; n < 4; n++)
						ocr[n] = rcvr_spi();
					ty = (ocr[0] & 0x40) ? 6 : 2;
				}
			}
		} else { /* SDC Ver1 or MMC */
			ty = (send_cmd(CMD55, 0) <= 1 && send_cmd(CMD41, 0) <= 1) ? 2 : 1; /* SDC : MMC */
			do {
				if (ty == 2) {
					if (send_cmd(CMD55, 0) <= 1 && send_cmd(CMD41, 0) == 0)
						break; /* ACMD41 */
				} else {
					if (send_cmd(CMD1, 0) == 0)
						break; /* CMD1 */
				}
			} while (Timer1);
			if (!Timer1 || send_cmd(CMD16, 512) != 0) /* Select R/W block length */
				ty = 0;
		}
	}
	CardType = ty;
	MySD_DESEL; /* CS = H */
	rcvr_spi(); /* Idle (Release DO) */

	if (ty) /* Initialization succeded */
		Stat &= ~STA_NOINIT; /* Clear STA_NOINIT */
	else
		/* Initialization failed */
		power_off();

	return Stat;
  /* USER CODE END INIT */
}
 
/**
  * @brief  Gets Disk Status 
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS USER_status (
	BYTE pdrv       /* Physical drive number to identify the drive */
)
{
  /* USER CODE BEGIN STATUS */
    if (pdrv)
		return STA_NOINIT; /* Supports only single drive */
	return Stat;
  /* USER CODE END STATUS */
}

/**
  * @brief  Reads Sector(s) 
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */
DRESULT USER_read (
	BYTE pdrv,      /* Physical drive nmuber to identify the drive */
	BYTE *buff,     /* Data buffer to store read data */
	DWORD sector,   /* Sector address in LBA */
	UINT count      /* Number of sectors to read */
)
{
  /* USER CODE BEGIN READ */
    if (pdrv || !count)
		return RES_PARERR;
	if (Stat & STA_NOINIT)
		return RES_NOTRDY;

	if (!(CardType & 4))
		sector *= 512; /* Convert to byte address if needed */

	MySD_SEL; /* CS = L */

	if (count == 1) { /* Single block read */
		if ((send_cmd(CMD17, sector) == 0) /* READ_SINGLE_BLOCK */
		&& rcvr_datablock(buff, 512))
			count = 0;
	} else { /* Multiple block read */
		if (send_cmd(CMD18, sector) == 0) { /* READ_MULTIPLE_BLOCK */
			do {
				if (!rcvr_datablock(buff, 512))
					break;
				buff += 512;
			} while (--count);
			send_cmd(CMD12, 0); /* STOP_TRANSMISSION */
		}
	}

	MySD_DESEL; /* CS = H */
	rcvr_spi(); /* Idle (Release DO) */

	return count ? RES_ERROR : RES_OK;
  /* USER CODE END READ */
}

/**
  * @brief  Writes Sector(s)  
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval DRESULT: Operation result
  */
#if _USE_WRITE == 1
DRESULT USER_write (
	BYTE pdrv,          /* Physical drive nmuber to identify the drive */
	const BYTE *buff,   /* Data to be written */
	DWORD sector,       /* Sector address in LBA */
	UINT count          /* Number of sectors to write */
)
{ 
  /* USER CODE BEGIN WRITE */
  /* USER CODE HERE */
    if (pdrv || !count)
		return RES_PARERR;
	if (Stat & STA_NOINIT)
		return RES_NOTRDY;
	if (Stat & STA_PROTECT)
		return RES_WRPRT;

	if (!(CardType & 4))
		sector *= 512; /* Convert to byte address if needed */

	MySD_SEL; /* CS = L */

	if (count == 1) { /* Single block write */
		if ((send_cmd(CMD24, sector) == 0) /* WRITE_BLOCK */
		&& xmit_datablock(buff, 0xFE))
			count = 0;
	} else { /* Multiple block write */
		if (CardType & 2) {
			send_cmd(CMD55, 0);
			send_cmd(CMD23, count); /* ACMD23 */
		}
		if (send_cmd(CMD25, sector) == 0) { /* WRITE_MULTIPLE_BLOCK */
			do {
				if (!xmit_datablock(buff, 0xFC))
					break;
				buff += 512;
			} while (--count);
			if (!xmit_datablock(0, 0xFD)) /* STOP_TRAN token */
				count = 1;
		}
	}

	MySD_DESEL; /* CS = H */
	rcvr_spi(); /* Idle (Release DO) */

	return count ? RES_ERROR : RES_OK;
  /* USER CODE END WRITE */
}
#endif /* _USE_WRITE == 1 */

/**
  * @brief  I/O control operation  
  * @param  pdrv: Physical drive number (0..)
  * @param  cmd: Control code
  * @param  *buff: Buffer to send/receive control data
  * @retval DRESULT: Operation result
  */
#if _USE_IOCTL == 1
DRESULT USER_ioctl (
	BYTE pdrv,      /* Physical drive nmuber (0..) */
	BYTE cmd,       /* Control code */
	void *buff      /* Buffer to send/receive control data */
)
{
  /* USER CODE BEGIN IOCTL */
    DRESULT res;
	BYTE n, csd[16], *ptr = buff;
	WORD csize;

	if (pdrv)
		return RES_PARERR;

	res = RES_ERROR;

	if (cmd == CTRL_POWER) {
		switch (*ptr) {
		case 0: /* Sub control code == 0 (POWER_OFF) */
			if (chk_power())
				power_off(); /* Power off */
			res = RES_OK;
			break;
		case 1: /* Sub control code == 1 (POWER_ON) */
			power_on(); /* Power on */
			res = RES_OK;
			break;
		case 2: /* Sub control code == 2 (POWER_GET) */
			*(ptr + 1) = (BYTE) chk_power();
			res = RES_OK;
			break;
		default:
			res = RES_PARERR;
		}
	} else {
		if (Stat & STA_NOINIT)
			return RES_NOTRDY;

		MySD_SEL; /* CS = L */

		switch (cmd) {
		case GET_SECTOR_COUNT: /* Get number of sectors on the disk (DWORD) */
			if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
				if ((csd[0] >> 6) == 1) { /* SDC ver 2.00 */
					csize = csd[9] + ((WORD) csd[8] << 8) + 1;
					*(DWORD*) buff = (DWORD) csize << 10;
				} else { /* MMC or SDC ver 1.XX */
					n = (csd[5] & 15) + ((csd[10] & 128) >> 7)
							+ ((csd[9] & 3) << 1) + 2;
					csize = (csd[8] >> 6) + ((WORD) csd[7] << 2)
							+ ((WORD) (csd[6] & 3) << 10) + 1;
					*(DWORD*) buff = (DWORD) csize << (n - 9);
				}
				res = RES_OK;
			}
			break;

		case GET_SECTOR_SIZE: /* Get sectors on the disk (WORD) */
			*(WORD*) buff = 512;
			res = RES_OK;
			break;

		case CTRL_SYNC: /* Make sure that data has been written */
			if (wait_ready() == 0xFF)
				res = RES_OK;
			break;

		case MMC_GET_CSD: /* Receive CSD as a data block (16 bytes) */
			if (send_cmd(CMD9, 0) == 0 /* READ_CSD */
			&& rcvr_datablock(ptr, 16))
				res = RES_OK;
			break;

		case MMC_GET_CID: /* Receive CID as a data block (16 bytes) */
			if (send_cmd(CMD10, 0) == 0 /* READ_CID */
			&& rcvr_datablock(ptr, 16))
				res = RES_OK;
			break;

		case MMC_GET_OCR: /* Receive OCR as an R3 resp (4 bytes) */
			if (send_cmd(CMD58, 0) == 0) { /* READ_OCR */
				for (n = 0; n < 4; n++)
					*ptr++ = rcvr_spi();
				res = RES_OK;
			}

//        case MMC_GET_TYPE :    /* Get card type flags (1 byte) */
//            *ptr = CardType;
//            res = RES_OK;
//            break;

		default:
			res = RES_PARERR;
		}

		MySD_DESEL; /* CS = H */
		rcvr_spi(); /* Idle (Release DO) */
	}

	return res;
  /* USER CODE END IOCTL */
}
#endif /* _USE_IOCTL == 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
