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

#ifndef FCD_H
#define FCD_H 1


#ifdef FCD
#define EXTERN
#define ASSIGN (x) =x
#else
#define EXTERN extern
#define ASSIGN(x)
#endif

#ifdef _WIN32
#define DONGLE_API_EXPORT __declspec(dllexport)
#define DONGLE_API_CALL  _stdcall
#else
#define DONGLE_API_EXPORT
#define DONGLE_API_CALL
#endif

#include <inttypes.h>





#ifdef __cplusplus
extern "C" {
#endif

/* Application functions */

typedef struct
{
    int type;
    float Data;
}MyDataType;

EXTERN DONGLE_API_EXPORT DONGLE_API_CALL MyDataType DongleGetADC(void);
EXTERN DONGLE_API_EXPORT DONGLE_API_CALL int DongleSetLED(int Status);
EXTERN DONGLE_API_EXPORT DONGLE_API_CALL uint8_t DongleGetData(uint8_t* Data);
EXTERN DONGLE_API_EXPORT DONGLE_API_CALL uint8_t DongleSendData(uint8_t* Data);
#ifdef __cplusplus
}
#endif

#endif // FCD_H
