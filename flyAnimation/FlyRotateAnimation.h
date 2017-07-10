#pragma once
#include "qwidget"
#include "qrect"
#include "qpoint"
class FlyRotateAnimationImpl;
class FlyRotateAnimation : QObject
{
public:
	FlyRotateAnimation(void);
	~FlyRotateAnimation(void);

	void setBitmap(const QString& path);
	void setBeginPoint(const QPoint& beginPt);
	void setEndPoint(const QPoint& endPt);
	void setDuration(int durationMs);
	void setRotateDuration(int durationMs);

	void start();
	void stop();
	bool isStart();

private:
	FlyRotateAnimationImpl* m_impl;

};

