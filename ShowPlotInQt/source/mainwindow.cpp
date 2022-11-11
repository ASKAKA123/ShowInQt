#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    util = new ShowUnityWindowsInQt(this);


    QString titleName("My project114514");

    connect(util, &ShowUnityWindowsInQt::unityProgramStarted, this, [&]()
    {
        util->setWindowParent((HWND)ui->tab->winId(), titleName);
    });

    // start your unity program
    QString unityExePath(R"(C:\Users\dwb\Desktop\My project114514\My project114514.exe)");
    util->startUnityProgram(unityExePath);

}

MainWindow::~MainWindow()
{
    delete ui;
}
