#include "widget.h"
#include "./ui_widget.h"
#include<iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString address=ui->le_address->text();
    int port=ui->le_port->text().toInt();

    udpclient=new imgUdpClient(address,port);


    connect(udpclient,&imgUdpClient::CvtQImageOK,this,[=]()
    {
        QPixmap p1(QPixmap::fromImage(udpclient->IMG()));
        ui->label->setPixmap(p1);
    });

    connect(udpclient,&imgUdpClient::SendMsg,this,[=](QString msg)
    {
        ui->textEdit->append(msg);
    });


    ui->pb_start->setCheckable(true);
    connect(ui->pb_start,&QPushButton::clicked,this,[=]()
    {
        if(ui->pb_start->isChecked()==true)
        {
            udpclient->StartRead();
            ui->pb_start->setText("stop");
        }
        else
        {
            udpclient->StopRead();
            ui->pb_start->setText("start");
            ui->label->setText("No Signal");
        }
    });
}

Widget::~Widget()
{
    delete ui;
}
