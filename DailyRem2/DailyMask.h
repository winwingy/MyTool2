#pragma once
#include "qtextedit.h"
class DailyMask : public QTextEdit
{
public:
	enum Level_mask
	{
		Level_mask_line,
		Level_mask_threeLine,
		Level_mask_clear,
	};
	DailyMask(QWidget* par);
	~DailyMask(void);
	void ColorTextByLine(int lineNumber, int columnNumber);
	void setMaskLevel(Level_mask level);

private:
	void initialize();
	void connection();
	virtual void resizeEvent(QResizeEvent * ev) override;
	virtual void keyPressEvent(QKeyEvent *e) override;
	virtual bool eventFilter(QObject *o, QEvent *e) override;
	void ColorTextByLineB(int lineNumber, int columnNumber);
	Level_mask m_level;
};
