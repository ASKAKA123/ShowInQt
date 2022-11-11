#include "showunitywindowsinqt.h"

ShowUnityWindowsInQt::ShowUnityWindowsInQt(QObject* parent)
    : QObject{parent}
{
    process = new QProcess(this);

    connect(process, &QProcess::started, this, &ShowUnityWindowsInQt::unityProgramStarted);
}

ShowUnityWindowsInQt::~ShowUnityWindowsInQt()
{
    process->kill();
}

void ShowUnityWindowsInQt::startUnityProgram(const QString& unityExePath)
{
    process->setProgram(unityExePath);
    process->start(QIODevice::Truncate);
    qDebug() << "PID: " << process->processId();
}

void ShowUnityWindowsInQt::setWindowParent(HWND parentWidgetHandle, const QString& sonWindowTitleName)
{
    HWND hfigure = FindWindow(NULL, sonWindowTitleName.toStdString().c_str());

    qDebug() << hfigure;

    if (NULL != ::SetParent(hfigure, parentWidgetHandle))
        qDebug() << "Success";
    else
        qDebug() << "Fail";
}
