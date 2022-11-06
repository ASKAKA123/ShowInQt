#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "imgudpclient.h"
#include <QThread>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

private:
    Ui::Widget *ui;

    imgUdpClient* udpclient;
};
#endif // WIDGET_H
