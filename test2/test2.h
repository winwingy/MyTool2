#ifndef TEST2_H
#define TEST2_H

#include <QtWidgets/QMainWindow>
#include "ui_test2.h"

class test2 : public QMainWindow
{
	Q_OBJECT

public:
	test2(QWidget *parent = 0);
	~test2();

public slots:
	void OnCursorPosChanged();
private:
	Ui::test2Class ui;
};

#endif // TEST2_H
