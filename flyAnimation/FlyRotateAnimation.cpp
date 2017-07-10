#include "stdafx.h"
#include "FlyRotateAnimation.h"
#include "FlyRotateAnimationImpl.h"


FlyRotateAnimation::FlyRotateAnimation(void)
	: m_impl(new FlyRotateAnimationImpl())
{
	m_impl->setHolder(this);
}


FlyRotateAnimation::~FlyRotateAnimation(void)
{
}

void FlyRotateAnimation::setBitmap(const QString& path)
{
	m_impl->setBitmap(path);
}

void FlyRotateAnimation::setBeginPoint(const QPoint& beginPt)
{
	m_impl->setBeginPoint(beginPt);
}

void FlyRotateAnimation::setEndPoint(const QPoint& endPt)
{
	m_impl->setEndPoint(endPt);
}

void FlyRotateAnimation::setDuration(int durationMs)
{
	m_impl->setDuration(durationMs);
}

void FlyRotateAnimation::setRotateDuration(int durationMs)
{
	m_impl->setRotateDuration(durationMs);
}

void FlyRotateAnimation::start()
{
	m_impl->start();
}

void FlyRotateAnimation::stop()
{
	m_impl->stop();
}

bool FlyRotateAnimation::isStart()
{
	return m_impl->isStart();
}
