#include "dialogstatus.h"
#include "ui_dialogstatus.h"

DialogStatus::DialogStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStatus)
{
    ui->setupUi(this);


    ui->comboFilaman->addItem("Off");
    ui->comboFilaman->addItem("Running");
    ui->comboFilaman->addItem("Stable");
    ui->comboFilaman->addItem("TimeOut");


    ui->comboHVC->addItem("Off");
    ui->comboHVC->addItem("Running");
    ui->comboHVC->addItem("Stable");
    ui->comboHVC->addItem("TimeOut");


    ui->comboHVV->addItem("Off");
    ui->comboHVV->addItem("Running");
    ui->comboHVV->addItem("Stable");
    ui->comboHVV->addItem("TimeOut");


    ui->comboHVT->addItem("Off");
    ui->comboHVT->addItem("Normal");
    ui->comboHVT->addItem("Min");
    ui->comboHVT->addItem("Max");


    ui->comboDETV->addItem("Off");
    ui->comboDETV->addItem("Running");
    ui->comboDETV->addItem("Stable");
    ui->comboDETV->addItem("TimeOut");


    ui->comboDETT->addItem("Off");
    ui->comboDETT->addItem("Running");
    ui->comboDETT->addItem("Stable");
    ui->comboDETT->addItem("TimeOut");
    ui->comboDETT->addItem("Min");
    ui->comboDETT->addItem("Max");


    ui->comboADCT->addItem("Off");
    ui->comboADCT->addItem("Running");
    ui->comboADCT->addItem("Stable");
    ui->comboADCT->addItem("TimeOut");
    ui->comboADCT->addItem("Min");
    ui->comboADCT->addItem("Max");

    ui->comboPMAT->addItem("Off");
    ui->comboPMAT->addItem("Normal");
    ui->comboPMAT->addItem("Min");
    ui->comboPMAT->addItem("Max");



    ui->comboDOOR->addItem("Unkwon");
    ui->comboDOOR->addItem("Open");
    ui->comboDOOR->addItem("Close");
    ui->comboDOOR->addItem("Openning");
    ui->comboDOOR->addItem("Closing");
    ui->comboDOOR->addItem("OpenTimeOut");
    ui->comboDOOR->addItem("CloseTimeOut");

    ui->comboPREP->addItem("OK");
    ui->comboPREP->addItem("Err");

    ui->comboPREN->addItem("OK");
    ui->comboPREN->addItem("Err");



}

DialogStatus::~DialogStatus()
{
    delete ui;
}

int DialogStatus::getData(uint8_t *data)
{
    //int Data[8];


//    data[0]=0;
//    data[1]=0;
//    data[2]=0;
//    data[3]=0;
//    data[4]=0;
//    data[5]=0;
    data[6]=0;
    data[7]=0;

    data[0]=(ui->comboFilaman->currentIndex()*0x0A);
    data[0]+=(ui->comboHVC->currentIndex());
    data[1]=(ui->comboHVV->currentIndex()*0x0A);
    data[1]+=(ui->comboHVT->currentIndex());
    data[2]=(ui->comboDETV->currentIndex()*0x0A);
    data[2]+=(ui->comboDETT->currentIndex());
    data[3]=(ui->comboADCT->currentIndex()* 0x0A);
    data[3]+=(ui->comboPMAT->currentIndex());
    data[4]=(ui->comboDOOR->currentIndex()* 0x0A);
    data[4]+=(ui->comboPREP->currentIndex());
    data[5]=(ui->comboPREN->currentIndex()* 0x0A);




    return 1;
}
