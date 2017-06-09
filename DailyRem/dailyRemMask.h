
#ifndef DAILYREM_MASK_H
#define DAILYREM_MASK_H
#include "qtextedit.h"


class DailyRemMask : public QTextEdit
{
	Q_OBJECT

public:
	DailyRemMask(QWidget *parent = 0);
	~DailyRemMask();

protected:
	virtual void paintEvent(QPaintEvent * e) override;

private:
	void init();
	void connection();
};

#endif // DAILYREM_H
