#pragma once
#include "qtextedit.h"

class DailyMask;
class DailyEdit : public QTextEdit
{
public:
	DailyEdit(QWidget* par);
	~DailyEdit(void);

protected:
	virtual void resizeEvent(QResizeEvent * ev) override;
	virtual void keyPressEvent(QKeyEvent *e) override;
	virtual bool eventFilter(QObject *o, QEvent *e) override;
	virtual void focusInEvent(QFocusEvent *e) override;
	virtual void mousePressEvent(QMouseEvent *e) override;

private:
	void initialize();
	void connection();

	void test();
	int getCursorLine(int* columnNumber);
	void onHotKey(QKeyEvent *e);
	void onCursorPositionChanged();
	DailyMask* m_mask;
};

