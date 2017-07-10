#pragma once
class QVariantAnimation;

class FlyRotateAnimationImpl  : public QWidget
{
public:
	FlyRotateAnimationImpl(void);
	~FlyRotateAnimationImpl(void);
	void setHolder(QObject* holder);
	void setBitmap(const QString& path);
	void setBeginPoint(const QPoint& beginPt);
	void setEndPoint(const QPoint& endPt);
	void setDuration(int durationMs);
	void setRotateDuration(int durationMs);

	void start();
	void stop();
	bool isStart();


private:
	virtual void paintEvent(QPaintEvent *ev) override;

	QObject* m_holder;
	bool m_isStart;
	QString m_picPath;
	QPixmap m_picPixmap;
	QPoint m_begPt;
	QPoint m_endPt;
	int m_durationMs;
	int m_durationMsRotate;
	QVariantAnimation* m_animation;
	QVariantAnimation* m_animationY;
	QVariantAnimation* m_animationRotate;
	qreal m_rotateValue;


};

