#include "stdafx.h"
#include "FlyRotateAnimationImpl.h"
#include "QPropertyAnimation"


FlyRotateAnimationImpl::FlyRotateAnimationImpl(void)
	: m_holder(nullptr)
	  , m_isStart(false)
	  , m_picPath()
	  , m_picPixmapxxxxxxxxxxxxxtttttttttttt()
	  , m_begPt()
	  , m_endPt()
	  , m_durationMs(0)
	  , m_durationMsRotate(0)
	  , m_animation(new QVariantAnimation(this))
	  , m_animationY(new QVariantAnimation(this))
	  , m_animationRotate(new QVariantAnimation(this))
	  , m_rotateValue(0.0)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
		Qt::WindowMinimizeButtonHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_DeleteOnClose);
}


FlyRotateAnimationImpl::~FlyRotateAnimationImpl(void)
{
	if (m_holder)
	{
		delete m_holder;
		m_holder = nullptr;
	}
}

void FlyRotateAnimationImpl::setHolder(QObject* holder)
{
	m_holder = holder;
}

void FlyRotateAnimationImpl::setBitmap(const QString& path)
{
	m_picPath = path;
	bool ret = m_picPixmapxxxxxxxxxxxxxtttttttttttt.load(path);
	Q_ASSERT(ret);
	setGeometry(0, 0, m_picPixmapxxxxxxxxxxxxxtttttttttttt.width(), m_picPixmapxxxxxxxxxxxxxtttttttttttt.height());
}

void FlyRotateAnimationImpl::setBeginPoint(const QPoint& beginPt)
{
	m_begPt = beginPt;
}

void FlyRotateAnimationImpl::setEndPoint(const QPoint& endPt)
{
	m_endPt = endPt;
}

void FlyRotateAnimationImpl::setDuration(int durationMs)
{
	m_durationMs = durationMs;
}

void FlyRotateAnimationImpl::setRotateDuration(int durationMs)
{
	m_durationMsRotate = durationMs;
}

void FlyRotateAnimationImpl::start()
{
	if (m_isStart)
		return;

	m_isStart = true;
	{
		m_animation->setDuration(m_durationMs);
		m_animation->setStartValue(m_begPt.x());
		m_animation->setEndValue(m_endPt.x());
		m_animation->setEasingCurve(QEasingCurve::Linear);
		QObject::connect(m_animation, &QPropertyAnimation::valueChanged,
		                 [&](const QVariant& value)
	                 {
		                 QRect pos = geometry();
		                 pos.moveLeft(value.toInt());
		                 this->setGeometry(pos);
	                 });
		QObject::connect(m_animation, &QPropertyAnimation::finished, [&]()
	                 {
		                 if (m_animationRotate->state() == QVariantAnimation::Stopped)
		                 {
			                 this->close();
		                 }
	                 });
		m_animation->start();
	}

	{
		m_animationY->setDuration(m_durationMs);
		m_animationY->setStartValue(m_begPt.y());
		m_animationY->setEndValue(m_endPt.y());
		m_animationY->setEasingCurve(QEasingCurve::OutBack);
		QObject::connect(m_animationY, &QPropertyAnimation::valueChanged,
		                 [&](const QVariant& value)
	                 {
		                 QRect pos = geometry();
		                 pos.moveTop(value.toInt());
		                 this->setGeometry(pos);
	                 });
		QObject::connect(m_animationY, &QPropertyAnimation::finished, [&]()
	                 {
		                 if (m_animationRotate->state() == QVariantAnimation::Stopped)
		                 {
			                 this->close();
		                 }
	                 });
		m_animationY->start();
	}

	{
		m_animationRotate->setDuration(m_durationMsRotate);
		m_animationRotate->setStartValue(0);
		m_animationRotate->setEndValue(m_durationMsRotate);
		m_animationRotate->setEasingCurve(QEasingCurve::Linear);
		QObject::connect(m_animationRotate,
		                 &QPropertyAnimation::valueChanged,
		                 [&](const QVariant& value)
	                 {
		                 m_rotateValue = value.toInt() * 1.2;
		                 update();
	                 });
		QObject::connect(m_animationRotate, &QPropertyAnimation::finished,
		                 [&]()
	                 {
		                 if (m_animation->state() == QVariantAnimation::Stopped)
		                 {
			                 this->close();
		                 }
	                 });
		m_animationRotate->start();
	}

	this->move(m_begPt);
	this->show();
}

void FlyRotateAnimationImpl::stop()
{
	close();
}

bool FlyRotateAnimationImpl::isStart()
{
	return m_isStart;
}

void FlyRotateAnimationImpl::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	QRect rotateRect(-rect().width() / 2, -rect().height() / 2,
	                 width(), height());
	int cx = rect().width() / 2;
	int cy = rect().height() / 2;
	painter.translate(cx, cy);
	painter.rotate(m_rotateValue);
	qDebug() << "m_rotateValue = " << m_rotateValue;
	painter.drawPixmap(rotateRect, m_picPixmapxxxxxxxxxxxxxtttttttttttt);
	__super::paintEvent(ev);
}
