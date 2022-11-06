//ReadMe
//author: pilot.phil
//date: 2022-4-24
//usage: read udp datagram(it trans iamge sequence),and convert the datagram to QImage and Opencv Mat
//
//ref1: https://forum.qt.io/topic/97367/how-to-send-images-through-socket
// How to send images through socket
//ref2: QImage �� cv::Mat ֮�����໥ת��
//
//1.when udp obj readyRead emit, read the udp datagram to obj like QNetworkDatagram _datagram
//2.get the data in _datagram.data() in the form of QByteArray
//3.convert QbyteArray to QImage in some way, which in function ByteArray2QImage()
//4.convert QImage to opencv Mat in some way, which in function QImage2CVMat()
//5.one convert finished, emit zaifinished signal like CvtQImageOK() and CvtCVMatOK()

#ifndef IMGUDPCLIENT_H
#define IMGUDPCLIENT_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QNetworkDatagram>
#include <QDebug>
#include <QImage>
#include <QBuffer>
#include <QDateTime>

class imgUdpClient : public QObject
{
    Q_OBJECT
public:
    explicit imgUdpClient(const QString& ip="127.0.0.1",const int port=8848,QObject *parent = nullptr);
    ~imgUdpClient();

    void StartRead();
    void StopRead();

private:
    /**
     * @brief readDatagram read udp datagram
     */
    void readDatagram();

    /**
     * @brief bytes2CvMat
     */
    void ByteArray2QImage();

    QString getCurrentTime();
    void log(QString str);

signals:
    void CvtQImageOK();
    void CvtCVMatOK();
    void SendMsg(QString msg);

private:
    QUdpSocket* _udp;
    QString _ip;
    int _port;
    QNetworkDatagram _datagram;
    QImage qimg;



    QString msg;

public:
    QImage IMG() const{return qimg;}
    QString MSG() const{return msg;}

    bool _enableCvImshow;
};

#endif // IMGUDPCLIENT_H
