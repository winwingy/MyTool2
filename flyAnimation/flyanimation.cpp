#include "stdafx.h"
#include "flyanimation.h"
#include "FlyRotateAnimation.h"

flyAnimation::flyAnimation(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

flyAnimation::~flyAnimation()
{

}

void flyAnimation::keyPressEvent(QKeyEvent *ev)
{
	switch (ev->key())
	{
	case Qt::Key_A:
		{
			FlyRotateAnimation* animation = new FlyRotateAnimation;
			animation->setBitmap(QString("D:\\test\\music.png"));
			animation->setBeginPoint(QPoint(300, 300));
			animation->setEndPoint(QPoint(1000, 500));
			animation->setDuration(2000);
			animation->setRotateDuration(2000);
			animation->start();
			break;
		}
	}
	__super::keyPressEvent(ev);
}
