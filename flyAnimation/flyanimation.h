#ifndef FLYANIMATION_H
#define FLYANIMATION_H

#include <QtWidgets/QMainWindow>
#include "ui_flyanimation.h"

class flyAnimation : public QMainWindow
{
	Q_OBJECT

public:
	flyAnimation(QWidget* parent = nullptr);
	~flyAnimation();

private:
	void keyPressEvent(QKeyEvent* ev) override;
	Ui::flyAnimationClass ui;
};

#endif // FLYANIMATION_H
