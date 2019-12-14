#include "myserial.h"
#include "windows.h"
#include "ftd2xx.h"
#include <QDebug>
#include <QString>

MySerial::MySerial()
{
}

int  MySerial::Open(int ch)
{
    FT_DEVICE ftDevice;
    FT_STATUS ftStatus;
    DWORD deviceID;
    char serialNumber[16];
    char description[64];

    ftStatus = FT_Open(ch, &FT_Handle_Serial);
    if(ftStatus != FT_OK) { // FT_Open failed
        qDebug() << "FT_Open FAILED!";
    }
    ftStatus = FT_GetDeviceInfo( FT_Handle_Serial,
                                 &ftDevice,
                                 &deviceID,
                                 serialNumber,
                                 description,
                                 NULL );



    ftStatus = FT_ResetDevice(FT_Handle_Serial);
    ftStatus = FT_SetBaudRate(FT_Handle_Serial,FT_BAUD_115200);
    ftStatus = FT_SetDataCharacteristics(
            FT_Handle_Serial,
            FT_BITS_8,
            FT_STOP_BITS_1,
            FT_PARITY_NONE
            );

    ftStatus = FT_SetFlowControl(
            FT_Handle_Serial,
            FT_FLOW_NONE,
            0x11,
            0x13
            );
}


int  MySerial::Close(void)
{
    FT_Close(FT_Handle_Serial);
}



int  MySerial::Read(void)
{

char Buf[256];
DWORD BytesRead = 0;
DWORD RxBytes = 0;
DWORD TxBytes = 0;
DWORD EventDWord = 0;
FT_GetStatus(FT_Handle_Serial,&RxBytes,&TxBytes,&EventDWord);

qDebug()<<"RxBytes:"<<RxBytes<<"TxBytes:"<<TxBytes<<"\r\n";

if(RxBytes>0)
{
    while (RxBytes > 0) {
        FT_Read(FT_Handle_Serial,Buf,RxBytes < 256 ? RxBytes : 256,&BytesRead);
        RxBytes -= BytesRead;
        for(int i=0;i<BytesRead;i++)
        {
            qDebug()<<Buf[i];
        }
    }
}
}

int MySerial::Write(void)
{


    FT_STATUS ftStatus;



    char Buf[256];

    char *s;
    Buf[0]='H';
    Buf[1]='e';
    Buf[2]='l';
    Buf[3]='l';
    Buf[4]='o';
    s = Buf;
    ULONG bytesWrite=5;

    ULONG bytesWritten=0;



    FT_Write(FT_Handle_Serial,s,bytesWrite,&bytesWritten);


}


int MySerial::FindMyDevice(int dev)
{
    FT_HANDLE FT_Handle;
    FT_DEVICE ftDevice;
    FT_STATUS FT_Status;
    DWORD deviceID;
    char serialNumber[16];
    char description[64];
    QString MyDesc;
    int MyDevFind=0;

    FT_Status = FT_Open(dev, &FT_Handle);
    if(FT_Status != FT_OK) { // FT_Open failed
        qDebug() << "FT_Open FAILED!";
    }
    FT_Status = FT_GetDeviceInfo( FT_Handle,
                                  &ftDevice,
                                  &deviceID,
                                  serialNumber,
                                  description,
                                  NULL );

    if (FT_Status == FT_OK)
    {
      MyDesc=QString::fromLatin1(description);
        qDebug()<<"Desc is:"<<MyDesc<<"\r\n";

        if (ftDevice == FT_DEVICE_2232H)
        {


            if ( MyDesc.contains("USB <-> CAN B"))
            {
                qDebug()<<"Find MyDevice B";
                MyDevFind=1;

            }


        }
        else if (ftDevice == FT_DEVICE_232R)
        {
             if ( MyDesc.contains("FT232R USB UART"))
            {
                qDebug()<<"FT232R USB UART";
                MyDevFind=1;

            }
        }
    }
    FT_Close(FT_Handle);

    return MyDevFind;
}


int MySerial::FindAllDevices(void)
{
    FT_STATUS FT_Status;
    FT_DEVICE_LIST_INFO_NODE *devInfo;
    DWORD numDevs=0;

    //
    // create the device information list
    //
    FT_Status = FT_CreateDeviceInfoList(&numDevs);
    if (FT_Status == FT_OK) {
        qDebug() << "Number of devices is "<<numDevs <<"\n";
    }

    //
    // allocate storage for list based on numDevs
    //
    devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);

    //
    // get the device information list
    //
    FT_Status = FT_GetDeviceInfoList(devInfo,&numDevs);
    if (FT_Status == FT_OK) {
        for (int i = 0; i < numDevs; i++) {
            qDebug() << "Dev: " << i<<"\n";
            qDebug() << "  Flags=0x"<<devInfo[i].Flags <<"\n";
            qDebug() << "  Type=0x"<<devInfo[i].Type<<"\n";
            qDebug() << "  ID=0x"<<devInfo[i].ID<<"\n";
            qDebug() << "  LocId=0x"<<devInfo[i].LocId<<"\n";
            qDebug() << "  SerialNumber="<<devInfo[i].SerialNumber<<"\n";
            qDebug() << "  Description="<<devInfo[i].Description<<"\n";
            qDebug() << "  FT_Handle=0x"<<devInfo[i].ftHandle<<"\n";
            qDebug() << "\r\n";
        }
    }

    return numDevs;

}

