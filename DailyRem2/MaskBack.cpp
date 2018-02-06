#include "StdAfx.h"
#include "MaskBack.h"
#include "qboxlayout"
#include "DailyMask.h"
#include "dailyrem2.h"

MaskBack::MaskBack(QWidget* par, DailyMask* child)
	: QLabel(par)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(child);
	m_daily = child;

	initialize();
	connection();
}


MaskBack::~MaskBack(void)
{
}

void MaskBack::initialize()
{
	setAttribute(Qt::WA_TransparentForMouseEvents);
}

void MaskBack::connection()
{
	QObject::connect(m_daily, &DailyMask::signalsSelRectChanged,
	                 [&](const std::vector<QRect>& selRect)
                 {
	                 m_test = 5;
	                 m_selRect = selRect;
	                 //update();
                 });
}

void MaskBack::paintEvent(QPaintEvent* ev)
{
	if (m_selRect.empty())
		return;

	QRect rectA = m_selRect[0];
	QRect rectB;
	if (m_selRect.size() > 1)
		rectB = m_selRect[1];

	if (rectA.isEmpty())
		return;

	QImage emptyImg(size().width(), size().height(), QImage::Format_ARGB32);
	emptyImg.fill(Qt::transparent);
	{
		QPainter painterImg(&emptyImg);
		//painterImg.begin(&emptyImg);
		//m_selRect.moveTo(0, 0);
		painterImg.fillRect(rectA, QBrush(Qt::green));
		if (!rectB.isEmpty())
			painterImg.fillRect(rectB, QBrush(Qt::yellow));
		//painterImg.end();
	}

	QImage img(size().width(), size().height(), QImage::Format_ARGB32);
	img.fill(Qt::transparent);
	{
		QPainter painterImg2;
		painterImg2.begin(&img);
		painterImg2.setCompositionMode(QPainter::CompositionMode_Source);
		painterImg2.fillRect(rect(), QBrush(Qt::white));

		painterImg2.setCompositionMode(QPainter::CompositionMode_DestinationOut);
		painterImg2.drawImage(rect(), emptyImg);

		painterImg2.end();
	}

	QPainter painter(this);
	painter.drawImage(0, 0, img);


	// 
	// 	QPixmap pix(size());
	// 	pix.fill(QColor(0, 255, 0, 225));
	// 	QPainter paintPix(&pix);
	// 	paintPix.setCompositionMode(QPainter::CompositionMode_DestinationOut);
	// 	paintPix.fillRect(m_selRect, QColor(255, 0, 0, 225));
	// 	paintPix.end();
	// 
	// 	QPainter painter(this);
	// 	painter.drawPixmap(0, 0, pix);


	// 	QPainter painter(this);
	// 	painter.fillRect(rect(), QColor(0, 0, 255, 225));
	// 	painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
	// 	
	// 	painter.fillRect(m_selRect, QColor(0, 255, 0, 225));
	__super::paintEvent(ev);
}
