#ifndef DAILYREM2_H
#define DAILYREM2_H

#include <QtWidgets/QMainWindow>

class DailyEdit;
class DailyRem2 : public QMainWindow
{
	Q_OBJECT

public:
	DailyRem2(QWidget *parent = 0);
	~DailyRem2();

private:
	virtual void resizeEvent(QResizeEvent *ev) override;	
	void initialize();
	void connection();

	DailyEdit* m_daily;
	QMenuBar* m_menuBar;
	QMenu* m_menu;

};

#endif // DAILYREM2_H
