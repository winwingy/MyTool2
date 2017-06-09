/********************************************************************************
** Form generated from reading UI file 'test2.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST2_H
#define UI_TEST2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *test2Class)
    {
        if (test2Class->objectName().isEmpty())
            test2Class->setObjectName(QStringLiteral("test2Class"));
        test2Class->resize(600, 400);
        menuBar = new QMenuBar(test2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        test2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(test2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        test2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(test2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        test2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(test2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        test2Class->setStatusBar(statusBar);

        retranslateUi(test2Class);

        QMetaObject::connectSlotsByName(test2Class);
    } // setupUi

    void retranslateUi(QMainWindow *test2Class)
    {
        test2Class->setWindowTitle(QApplication::translate("test2Class", "test2", 0));
    } // retranslateUi

};

namespace Ui {
    class test2Class: public Ui_test2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST2_H
