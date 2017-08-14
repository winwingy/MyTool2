#include "stdafx.h"
#include "dailyrem2.h"
#include "DailyEdit.h"
#include "qboxlayout.h"
#include "qstatusbar.h"
#include "tool\config.h"
#include "qmenubar.h"

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
	setGeometry(100, 100, 1200, 800);	
	QWidget* center = new QWidget(this);
	setCentralWidget(center);
	QHBoxLayout* layout = new QHBoxLayout(center);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(m_daily);

	m_menu = menuBar()->addMenu(QString::fromStdWString(L"ÎÄ¼ş"));
	QAction* openAction = new QAction(this);
	openAction->setText("open");
	QObject::connect(openAction, &QAction::triggered, [&]()
	{
		m_daily->openFile();
	});	

	QAction* saveAction = new QAction(this);
	saveAction->setText("save");
	QObject::connect(saveAction, &QAction::triggered, [&]()
	{
		m_daily->saveFile();
	});

	m_menu->addAction(openAction);
	m_menu->addAction(saveAction);
}

void DailyRem2::connection()
{
	QObject::connect(m_daily, &DailyEdit::cursorPositionChangedEx, 
		[&](int row, int column)
	{
		statusBar()->showMessage(QString("row=%1 , column=%2").arg(row).arg(column));
	});
}

void DailyRem2::resizeEvent(QResizeEvent *ev)
{
// 	QRect rc = m_menuBar->rect();
// 	bool isVis = m_menuBar->isVisible();
// 	QRect menuRect = m_menu->rect();
// 	isVis = m_menu->isVisible();
// 	QObject* par = m_menu->parent();
// 	QObject*  parBar = m_menuBar->parent();


	__super::resizeEvent(ev);
}
