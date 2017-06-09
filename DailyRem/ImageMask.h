#pragma once
#include "qlabel.h"
class ImageMask : public QLabel
{
	Q_OBJECT
public:
	ImageMask(QWidget* par);
	~ImageMask(void);
	void setPixmap(const QPixmap & pix);
	void setClearArea(const QRect& clearArea);

protected:
	virtual void paintEvent(QPaintEvent *e) override;

private:
	QPixmap m_pixmap;
	QRect m_clearArea;
};

