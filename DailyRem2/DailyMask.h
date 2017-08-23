#pragma once
#include "qtextedit.h"
class DailyMask : public QTextEdit
{
	Q_OBJECT
public:
	enum Level_mask
	{
		Level_mask_line,
		Level_mask_threeLine,
		Level_mask_clear,
		Level_mask_all,
	};
	DailyMask(QWidget* par);
	~DailyMask(void);

	void ColorTextByLine(int lineNumber, int columnNumber);
	void ColorTextByRect(const QRect& rc);
	void setMaskLevel(Level_mask level);

signals:
	void signalsSelRectChanged(const std::vector<QRect>& selRect);

private:
	void initialize();
	void connection();
	virtual void resizeEvent(QResizeEvent * ev) override;
	virtual void keyPressEvent(QKeyEvent *e) override;
	virtual bool eventFilter(QObject *o, QEvent *e) override;
	void ColorTextByLineB(int lineNumber, int columnNumber);
	Level_mask m_level;
	int m_lineHeight;
};

