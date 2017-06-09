#include "stdafx.h"
#include "dailyrem.h"
#include <QFileDialog>
#include <QRect>
#include <qDebug>
#include "dailyRemMask.h"

DailyRem::DailyRem(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connection();
}

QRect getAdjustRectByWidth(const QRect& rect, int width, int maxWidth)
{
	QRect rectRet(rect);
	int left = rect.left() - width/2;
	if (left < 0)
		left = 0;

	int right = rect.right() + width/2;
	if (right > maxWidth)
		right = maxWidth;

	rectRet.setLeft(left);
	rectRet.setRight(right);
	return rectRet;
}

void DailyRem::connection()
{

}

DailyRem::~DailyRem()
{

}

void DailyRem::init()
{
	ui.m_dailyEdit->setMaskText(QString());
}
