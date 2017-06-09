#include "stdafx.h"
#include "dailyRemMask.h"
#include <QFileDialog>
#include <QRect>
#include <qDebug>
#include "qwidget.h"

namespace
{

}

DailyRemMask::DailyRemMask(QWidget *parent)
	: QTextEdit(parent)
{	
	init();
	connection();
}

void DailyRemMask::init()
{
	setWindowTitle("DailyRemMask");
	
	QPalette pal;
	pal.setColor(QPalette::Base, QColor(255, 0, 0, 125));
	setPalette(pal);
	setStyleSheet("QTextEdit{border: none;}");

// 	setAttribute(Qt::WA_TranslucentBackground);
// 	setFrameStyle(QFrame::NoFrame);   

// 	QGraphicsOpacityEffect *e3 = new QGraphicsOpacityEffect(this);
// 	e3->setOpacity(0.7);
// 	setGraphicsEffect(e3);

	//setAttribute(Qt::WA_TranslucentBackground, true);
// 	QGraphicsEffect eff;
// 	QGraphicsEffect
// 	QGraphicsOpacityEffect effect;
// 	effect.setOpacity(0);
// 	setGraphicsEffect(effect);
	 //QMetaObject::connectSlotsByName(DailyRemMask);
// 	setStyleSheet("{border: transparent;background: transparent;}");
// 	setAttribute(Qt::WA_TranslucentBackground);
// 	QPalette* pal = (QPalette*)&palette();
// 	pal->setBrush(QPalette::Base, QBrush(QColor(0, 0, 0, 0)));
// 	setPalette(*pal);
}

void DailyRemMask::connection()
{
	
}

DailyRemMask::~DailyRemMask()
{

}

void DailyRemMask::paintEvent(QPaintEvent * e)
{
// 	QPainter pter(this);
// 	pter.fillRect(rect(), QBrush(QColor(0, 88, 0, 33)));
	__super::paintEvent(e);
}
