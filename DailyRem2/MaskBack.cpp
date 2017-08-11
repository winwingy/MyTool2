#include "StdAfx.h"
#include "MaskBack.h"
#include "qboxlayout"
#include "DailyMask.h"

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

}

void MaskBack::connection()
{
	QObject::connect(m_daily, &DailyMask::signalsSelRectChanged, 
		[&](const QRect& selRect)
	{
		qDebug() << m_selRect;
		m_selRect = selRect;
		qDebug() << m_selRect;
		update();
	});
}

void MaskBack::paintEvent(QPaintEvent * ev)
{
	QImage emptyImg(m_selRect.width(), m_selRect.height(), QImage::Format_ARGB32);
	emptyImg.fill(Qt::transparent);
	{
		QPainter painterImg(&emptyImg);
		//painterImg.begin(&emptyImg);
		m_selRect.moveTo(0, 0);
		painterImg.fillRect(m_selRect, QBrush(Qt::transparent));
		//painterImg.end();
	}

	QImage img(size().width(), size().height(), QImage::Format_ARGB32);
	img.fill(Qt::transparent);
	{
		QPainter painterImg2;
		painterImg2.begin(&img);
		painterImg2.setCompositionMode(QPainter::CompositionMode_Source);
		painterImg2.fillRect(rect(), QBrush(Qt::white));

		painterImg2.setCompositionMode(QPainter::CompositionMode_SourceOut);
		painterImg2.drawImage(m_selRect, emptyImg);

		painterImg2.end();
	}


	



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
