#pragma once
#include <QTextEdit>
class TextEditMask : public QTextEdit
{
	Q_OBJECT
public:
	TextEditMask(QWidget* par);
	~TextEditMask(void);
	void setClearArea(const QRect& rc);	
	void ColorTextCharFormat(const QString& search_text);
	void ColorTextByLine(int lineNumber);

signals:
	void signalFocusIn();

protected:
	virtual void mousePressEvent(QMouseEvent *e) override;
	virtual void focusInEvent(QFocusEvent *e) override;
	virtual void paintEvent(QPaintEvent *e) override;
	bool eventFilter(QObject* o, QEvent* e);

private:
	QRect m_clearArea;
};

