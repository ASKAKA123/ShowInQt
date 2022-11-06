#include "widget.h"
#include "./ui_widget.h"
#include <Windows.h>
#include <winuser.h>
#include <QDebug>
#include <qdialog.h>
#include "shlwapi.h"

Widget::Widget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);
    set("UnityEditor.GameView");
}


Widget::~Widget()
{
	delete ui;
}

void Widget::set(const QString& winName)
{
	HWND centralWidget = (HWND)(ui->mdiArea->winId());
	HWND hfigure = FindWindow(NULL, winName.toStdString().c_str());

	qDebug() << hfigure;

	if (NULL == ::SetParent(hfigure, centralWidget))
	{

	}
	else
	{

	}
}

void Widget::set(HWND parent, HWND son)
{
	auto res = ::SetParent(son, parent);
	qDebug() << res;
}

void Widget::set(HWND son)
{
	HWND centralWidget = (HWND)(ui->mdiArea->winId());
	set(son, centralWidget);
}
