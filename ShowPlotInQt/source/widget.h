#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

    void set(const QString& winName);

    void set(HWND parent, HWND son);

    void set(HWND son);

private:
    Ui::Widget* ui;
};
#endif // WIDGET_H
