#include "stdafx.h"
#include "TextEditMask.h"


TextEditMask::TextEditMask(QWidget* par)
	: QTextEdit(par)
{
	//setFocusPolicy(Qt::NoFocus);

	QPalette pal;
	pal.setColor(QPalette::Base, QColor(255, 0, 0, 0));
	pal.setColor(QPalette::HighlightedText, QColor(0, 255, 0, 50));
	this->setPalette(pal);
	this->setStyleSheet("QTextEdit{border: none;}");
}


TextEditMask::~TextEditMask(void)
{
}

void TextEditMask::focusInEvent(QFocusEvent *e)
{
	__super::focusInEvent(e);
	//emit signalFocusIn();
}

void TextEditMask::mousePressEvent(QMouseEvent *e)
{
	__super::mousePressEvent(e);
	//emit signalFocusIn();
}

bool TextEditMask::eventFilter(QObject* o, QEvent* e)
{
	return __super::eventFilter(o, e);

}

void TextEditMask::paintEvent(QPaintEvent *e)
{	
// 	QPainter painter(this);
// 	//painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
// 	//painter.setPen(Qt::NoPen);
// 	painter.setBrush(Qt::yellow);
// 	painter.drawRect(m_clearArea);
// 	painter.drawText(100, 100, "TextEditMask::paintEvent(QPaintEvent *e)");
	__super::paintEvent(e);
// 	QPainter 
// 	QPainter painter(this);
// 	painter.pix

}

void TextEditMask::setClearArea(const QRect& rc)
{
	m_clearArea = rc;
	update();
}
