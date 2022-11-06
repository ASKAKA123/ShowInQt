#include "imgudpclient.h"

imgUdpClient::imgUdpClient(const QString& ip,const int port,QObject *parent)
    : QObject{parent},_ip(ip),_port(port)
{
    _enableCvImshow=false;
}

imgUdpClient::~imgUdpClient()
{
    delete _udp;
}

void imgUdpClient::StartRead()
{
    readDatagram();

    log("Start Read Datagram!");

}

void imgUdpClient::StopRead()
{
    if(_udp!=nullptr)
        delete _udp;

    log("Stop Read Datagram!");

}

void imgUdpClient::readDatagram()
{
    _udp=new QUdpSocket();
    QHostAddress hostAddress(_ip);
    _udp->bind(hostAddress,_port);

    connect(_udp,&QUdpSocket::readyRead,this,[=]()
    {
        while (_udp->hasPendingDatagrams())
        {
            _datagram = _udp->receiveDatagram();

            msg="Received datagram size: "+QString::number(_datagram.data().size());
            log(msg);
            qDebug()<<msg;

            this->ByteArray2QImage();
        }
    });


}

void imgUdpClient::ByteArray2QImage()
{
    QBuffer imgb;
    imgb.open(QIODevice::ReadWrite);
    QByteArray temp=this->_datagram.data();
    imgb.write(temp);
    qimg.loadFromData(imgb.data());
    emit CvtQImageOK();
}


QString imgUdpClient::getCurrentTime()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("[hh:mm:ss]: "); //设置显示格式
    return str;
}

void imgUdpClient::log(QString str)
{
    auto time=this->getCurrentTime();
    auto msg=time+str;
    emit SendMsg(msg);
}






