#include "dailyrem2.h"
#include "DailyEdit.h"
#include "qboxlayout.h"

DailyRem2::DailyRem2(QWidget *parent)
	: QMainWindow(parent)
	, m_daily(new DailyEdit(this))
{
	
	initialize();
	connection();
}

DailyRem2::~DailyRem2()
{

}

void DailyRem2::initialize()
{
	QWidget* center = new QWidget(this);
	setCentralWidget(center);
	QHBoxLayout* layout = new QHBoxLayout(center);
	layout->setMargin(0);
	layout->addWidget(m_daily);
	setGeometry(100, 100, 1000, 800);
}

void DailyRem2::connection()
{

}

void DailyRem2::resizeEvent(QResizeEvent *ev)
{

	__super::resizeEvent(ev);
}
