/***************************************************************************
 *  This file is part of Qthid.
 * 
 *  Copyright (C) 2010  Howard Long, G6LVB
 *  CopyRight (C) 2011  Alexandru Csete, OZ9AEC
 *                      Mario Lorenz, DL5MLO
 * 
 *  Qthid is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Qthid is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Qthid.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***************************************************************************/

#define FCD
#include <string.h>
#ifdef WIN32
    #include <malloc.h>
#else
    #include <stdlib.h>
#endif
#include "hidapi.h"
#include "fcd.h"
#include <stdio.h>

//#include <qdebug.h>

#define FALSE 0
#define TRUE 1
typedef int BOOL;

const unsigned short _usVID=0x0483;// /*!< USB vendor ID. */
const unsigned short _usPID=0x5750;// /*!< USB product ID. */


union  ftob
{
    float f;
    unsigned char b[4];
};

union  ftob Myftob;



/** \brief Open FCD device.
  * \return Pointer to the FCD HID device or NULL if none found
  *
  * This function looks for FCD devices connected to the computer and
  * opens the first one found.
  */
static hid_device *fcdOpen(void)
{
    struct hid_device_info *phdi=NULL;
    hid_device *phd=NULL;
    char *pszPath=NULL;



    phdi=hid_enumerate(_usVID,_usPID);
    if (phdi==NULL)
    {
        printf("err hid_enumerate\r\n");
        return NULL; // No FCD device found
    }

    pszPath=strdup(phdi->path);

    if (pszPath==NULL)
    {
        return NULL;
    }

    hid_free_enumeration(phdi);
    phdi=NULL;

    if ((phd=hid_open_path(pszPath)) == NULL)
    {
        free(pszPath);
        pszPath=NULL;

        return NULL;
    }

    free(pszPath);
    pszPath=NULL;

    return phd;
}


/** \brief Close FCD HID device. */
static void fcdClose(hid_device *phd)
{
    hid_close(phd);
}






EXTERN DONGLE_API_EXPORT DONGLE_API_CALL uint8_t DongleSendData(uint8_t* Data)
{

    hid_device *phd=NULL;
    unsigned char aucBufOut[64+1];

    phd = fcdOpen();

    if (phd == NULL)
    {
        printf("phd == NULL\r\n");
        return 0;
    }

    for(int i=0;i<64;i++)
    {
        aucBufOut[i+1]=Data[i];
    }
    hid_write(phd, aucBufOut, 64);
    fcdClose(phd);
    phd = NULL;


    return 1;
}

EXTERN DONGLE_API_EXPORT DONGLE_API_CALL uint8_t DongleGetData(uint8_t* Data)
{
    hid_device *phd=NULL;
    uint8_t  HID_Data[64];

    phd = fcdOpen();

    if (phd == NULL)
    {
         printf("phd == NULL\r\n");
        return 0;
    }

    hid_read(phd, HID_Data, 64);
    fcdClose(phd);
    phd = NULL;

    memcpy(Data,HID_Data,64);
    return 1;

}



