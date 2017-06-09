#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "DailyEdit.h"

class DailyRemUi
{
public:
	DailyRemUi();

	void setupUi(QMainWindow *DailyRemClass);
	void CreateMainBody(QGridLayout* layout);
	void retranslateUi(QMainWindow *DailyRemClass);


	QAction *action_open;
	QAction *action_save;
	QAction *action_confusion;
	QWidget *centralWidget;

	QGridLayout *gridLayout;

	DailyEdit* m_dailyEdit;

	QStatusBar *statusBar;
	QMenuBar *menuBar;
	QMenu *menu;
	QMenu *menu_2;
};

