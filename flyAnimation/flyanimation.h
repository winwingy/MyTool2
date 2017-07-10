#ifndef FLYANIMATION_H
#define FLYANIMATION_H

#include <QtWidgets/QMainWindow>
#include "ui_flyanimation.h"

class flyAnimation : public QMainWindow
{
	Q_OBJECT

public:
	flyAnimation(QWidget *parent = 0);
	~flyAnimation();

private:
	virtual void keyPressEvent(QKeyEvent *ev) override;
	Ui::flyAnimationClass ui;
};

#endif // FLYANIMATION_H
