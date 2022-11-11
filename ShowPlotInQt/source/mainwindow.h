#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <showunitywindowsinqt.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    ShowUnityWindowsInQt* util;
};

#endif // MAINWINDOW_H
