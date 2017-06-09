#pragma once
#include <QTextEdit>
#include <QResizeEvent>
class TextEditMask;
class QLabel;

class DailyEdit : public QTextEdit
{
	Q_OBJECT
public:
	DailyEdit(void);
	~DailyEdit(void);
	void setMaskText(const QString& text);

public slots:
	void OnCursorPositionChanged();
	void OnTextChanged();

protected:
	virtual void resizeEvent(QResizeEvent *) override;

private:
	void initialize();
	void connection();

	TextEditMask* m_textMask;
	QLabel* m_maskCover;
};

