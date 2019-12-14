#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include <QDateTime>
#include "windows.h"
#include <QTimer>
#include <stdio.h>
#include "hidapi.h"
#include "fcd.h"



class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};



MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    // create a timer
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()),
            this, SLOT(MyTimerSlot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MySleep(qint64 milliseconds){
    qint64 timeToExitFunction = QDateTime::currentMSecsSinceEpoch()+milliseconds;
    while(timeToExitFunction>QDateTime::currentMSecsSinceEpoch()){
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void MainWindow::Proccess_HID_Data_MCU_to_PC(uint8_t* data)
{
    if(data[0]==0xAA)
    {
        if (data[1] == 0)
        {
            ui->ckSW1->setChecked(0);
        }
        else
        {
            ui->ckSW1->setChecked(1);
        }

        if (data[2] == 0)
        {
            ui->ckSW2->setChecked(0);
        }
        else
        {
            ui->ckSW2->setChecked(1);
        }

        if (data[3] == 0)
        {
            ui->ckSW3->setChecked(0);
        }
        else
        {
            ui->ckSW3->setChecked(1);
        }

        if (data[4] == 0)
        {
            ui->ckSW4->setChecked(0);
        }
        else
        {
            ui->ckSW4->setChecked(1);
        }

        ui->lcdNumber->display(data[5]);

    }
}



void MainWindow::Send_HID_Data_PC_to_MCU(void)
{

    uint8_t writeData[64];
    writeData[0] = 0x55;


    if (ui->ckReceiveData->checkState())
    {
        writeData[1] = 1;
    }
    else
    {
        writeData[1] = 0;
    }

    if (ui->ckLED1->checkState())
    {
        writeData[2] = 1;
    }
    else
    {
        writeData[2] = 0;
    }

    if (ui->ckLED2->checkState())
    {
        writeData[3] = 1;
    }
    else
    {
        writeData[3] = 0;
    }


    if (ui->ckLED3->checkState())
    {
        writeData[4] = 1;
    }
    else
    {
        writeData[4] = 0;
    }

   DongleSendData(writeData);
}



void MainWindow::on_ckLED3_stateChanged(int arg1)
{
Send_HID_Data_PC_to_MCU();
}

void MainWindow::on_ckLED2_stateChanged(int arg1)
{
Send_HID_Data_PC_to_MCU();
}

void MainWindow::on_ckLED1_stateChanged(int arg1)
{
Send_HID_Data_PC_to_MCU();
}

void MainWindow::on_ckReceiveData_stateChanged(int arg1)
{
Send_HID_Data_PC_to_MCU();
}

void MainWindow::MyTimerSlot()
{
    uint8_t buf[64];
    char ValStr[30];

    DongleGetData(buf);

    Proccess_HID_Data_MCU_to_PC(buf);

    int wrap=0;

    ui->txtResp->setText("");
    QString NewDataStr="";
    for(int i=0;i<64;i++)
    {
        sprintf(ValStr,"%2X ",(uint8_t)buf[i]);

        NewDataStr.append(ValStr);
        wrap++;
        if(wrap>15)
        {
            wrap=0;
            NewDataStr.append("\r\n");
        }
    }
    ui->txtResp->append(NewDataStr);


}


void MainWindow::on_btnClearResp_clicked()
{
    ui->txtResp->clear();
}


void MainWindow::on_pbOpenHID_clicked()
{
     timer->start(100);
}
