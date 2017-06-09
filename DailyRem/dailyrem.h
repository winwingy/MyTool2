#ifndef DAILYREM_H
#define DAILYREM_H

#include <QtWidgets/QMainWindow>
#include "dailyremUi.h"
class DailyRemMask;

class DailyRem : public QMainWindow
{
	Q_OBJECT

public:
	DailyRem(QWidget *parent = 0);
	~DailyRem();
	void init();

private:
	
	void connection();
	DailyRemUi ui;
};

#endif // DAILYREM_H
