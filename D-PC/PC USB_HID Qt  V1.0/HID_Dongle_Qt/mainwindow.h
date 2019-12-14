#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "windows.h"
#include "ftd2xx.h"
#include "myserial.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    




public:
#define MY_VID 0x0483
#define MY_PID 0x5750
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   static BYTE Myspi_readwrite(BYTE);
   void ProcessNewData(uint32_t rxId, uint8_t len, uint8_t rxBuf[]);
    QTimer *timer;
    QTimer * Irq_timer;
    MySerial *Serial;


public slots:
    void MyTimerSlot();
    //void IrqTimerSlot();
    
private slots:

    void on_btnClearResp_clicked();
    void on_pbCloseSerial_clicked();
    void on_pbOpenSerial_clicked();
    void on_pbGetSerialStatus_clicked();
    void on_pbWriteSerial_clicked();


    void on_ckLED3_stateChanged(int arg1);

    void on_ckLED2_stateChanged(int arg1);

    void on_ckLED1_stateChanged(int arg1);

    void on_ckReceiveData_stateChanged(int arg1);

    void Proccess_HID_Data_MCU_to_PC(uint8_t* data);
    void Send_HID_Data_PC_to_MCU(void);

    void on_pbOpenHID_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
