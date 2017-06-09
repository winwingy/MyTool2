#include "dailyremUi.h"

DailyRemUi::DailyRemUi()
{

}


void DailyRemUi::setupUi(QMainWindow *ParentClass)
{
	if (ParentClass->objectName().isEmpty())
		ParentClass->setObjectName(QStringLiteral("DailyRemClass"));
	ParentClass->resize(600, 400);
	action_open = new QAction(ParentClass);
	action_open->setObjectName(QStringLiteral("action_open"));
	action_save = new QAction(ParentClass);
	action_save->setObjectName(QStringLiteral("action_save"));
	action_confusion = new QAction(ParentClass);
	action_confusion->setObjectName(QStringLiteral("action_confusion"));
	centralWidget = new QWidget(ParentClass);
	centralWidget->setObjectName(QStringLiteral("centralWidget"));
	gridLayout = new QGridLayout(centralWidget);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(11, 11, 11, 11);
	gridLayout->setObjectName(QStringLiteral("gridLayout"));
	gridLayout->setContentsMargins(0, 0, 0, 0);

	CreateMainBody(gridLayout);

	ParentClass->setCentralWidget(centralWidget);
	statusBar = new QStatusBar(ParentClass);
	statusBar->setObjectName(QStringLiteral("statusBar"));
	ParentClass->setStatusBar(statusBar);
	menuBar = new QMenuBar(ParentClass);
	menuBar->setObjectName(QStringLiteral("menuBar"));
	menuBar->setGeometry(QRect(0, 0, 600, 23));
	menu = new QMenu(menuBar);
	menu->setObjectName(QStringLiteral("menu"));
	menu_2 = new QMenu(menuBar);
	menu_2->setObjectName(QStringLiteral("menu_2"));
	ParentClass->setMenuBar(menuBar);

	menuBar->addAction(menu->menuAction());
	menuBar->addAction(menu_2->menuAction());
	menu->addAction(action_open);
	menu->addAction(action_save);
	menu_2->addAction(action_confusion);

	retranslateUi(ParentClass);

	QMetaObject::connectSlotsByName(ParentClass);
} // setupUi

void DailyRemUi::CreateMainBody(QGridLayout* layout)
{
	m_dailyEdit = new DailyEdit;
	layout->addWidget(m_dailyEdit);
}

void DailyRemUi::retranslateUi(QMainWindow *DailyRemClass)
{
	DailyRemClass->setWindowTitle(QApplication::translate("DailyRemClass", "DailyRem", 0));
	action_open->setText(QApplication::translate("DailyRemClass", "\346\211\223\345\274\200", 0));
	action_save->setText(QApplication::translate("DailyRemClass", "\344\277\235\345\255\230", 0));
	action_confusion->setText(QApplication::translate("DailyRemClass", "\346\267\267\346\226\207", 0));
	menu->setTitle(QApplication::translate("DailyRemClass", "\346\226\207\344\273\266", 0));
	menu_2->setTitle(QApplication::translate("DailyRemClass", "\347\274\226\350\276\221", 0));
} // retranslateUi

