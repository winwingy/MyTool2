#include "stdafx.h"
#include "ImageMask.h"


ImageMask::ImageMask(QWidget* par)
	: QLabel(par)
	, m_pixmap()
	, m_clearArea()
{

}


ImageMask::~ImageMask(void)
{
}

void ImageMask::setClearArea(const QRect& clearArea)
{
	m_clearArea = clearArea;
}

void ImageMask::paintEvent(QPaintEvent *e)
{
	QPainter pter(this);
	pter.drawPixmap(rect(), m_pixmap);
	pter.setCompositionMode(QPainter::CompositionMode_SourceOut);
	pter.setPen(Qt::NoPen);
	pter.drawRect(m_clearArea);
}
