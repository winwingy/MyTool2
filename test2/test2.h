#ifndef TEST2_H
#define TEST2_H

#include <QtWidgets/QMainWindow>
#include "ui_test2.h"

class test2 : public QMainWindow
{
	Q_OBJECT

public:
	test2(QWidget *parent = 0);
	~test2();

public slots:
	void OnCursorPosChanged();
private:
	Ui::test2Class ui;
};

#endif // TEST2_H


// myTextDraw.h
#pragma once
#include "stdafx.h"
// 绘制QTextDocument中的指定区域
void drawDocument(QPainter* painter, 
	const QTextDocument* doc,
	const QRectF& r,
	const QBrush& brush = Qt::NoBrush/*brush to draw all content.used for shadow draw*/);
// 绘制Block及其内容
void drawTextLayout(QPainter* painter, 
	const QTextBlock& block, 
	const QSizeF& sizeToFill,
	const QBrush& brush);
// 绘制文本及其内外边
void drawText(QPainter* painter, 
	QPointF& p, 
	QString& text, 
	const QTextCharFormat& fmt,  
	const QBrush& brush);
qreal alignPos(Qt::Alignment a, 
	const qreal& width, 
	const qreal& textWidth);
bool needDrawText(const QTextCharFormat& chf);
void clearLetterSpacing(QTextDocument* doc, int* blockNum = NULL);
void adjustAlignJustify(QTextDocument* doc, qreal DocWidth, int* blockNum = NULL);
