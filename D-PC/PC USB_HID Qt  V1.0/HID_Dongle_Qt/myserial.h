#ifndef MYSERIAL_H
#define MYSERIAL_H
#include "windows.h"
#include "ftd2xx.h"


class MySerial
{

private:
    BYTE SendBuffer[20];
    BYTE ReceiveBuffer[20];

public:
    MySerial();
    int  Open(int ch);

    int  Close(void);

    int Write(void);
    int Read(void);
    int FindMyDevice(int dev);

    int FindAllDevices(void);

    FT_HANDLE FT_Handle_Serial;

};

#endif // MYSERIAL_H
