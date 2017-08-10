#include "stdafx.h"
#include "dailyrem2.h"
#include "DailyEdit.h"
#include "qboxlayout.h"
#include "qstatusbar.h"
#include "tool\config.h"

DailyRem2::DailyRem2(QWidget *parent)
	: QMainWindow(parent)
	, m_daily(new DailyEdit(this))
{
	if (!ConfigWy::GetShared()->Init(_T(".\\config.ini")))
		ConfigWy::GetShared()->Init(_T("..\\DailyRem2\\config.ini"));

	 m_daily = new DailyEdit(this);
	initialize();
	connection();
}

DailyRem2::~DailyRem2()
{

}

void DailyRem2::initialize()
{
	QStatusBar* statusBar = new QStatusBar(this);
	statusBar->setObjectName(QStringLiteral("statusBar"));
	setStatusBar(statusBar);

	QWidget* center = new QWidget(this);
	setCentralWidget(center);
	QHBoxLayout* layout = new QHBoxLayout(center);
	layout->setMargin(0);
	layout->addWidget(m_daily);
	setGeometry(100, 100, 1000, 800);
}

void DailyRem2::connection()
{
	QObject::connect(m_daily, &DailyEdit::cursorPositionChangedEx, 
		[&](int row, int column)
	{
		statusBar()->showMessage(QString("x=%1 , y=%2").arg(row).arg(column));
	});
}

void DailyRem2::resizeEvent(QResizeEvent *ev)
{

	__super::resizeEvent(ev);
}
