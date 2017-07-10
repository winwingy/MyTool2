#pragma once
#include <QTextEdit>
#include <QResizeEvent>
class TextEditMask;
class QLabel;
class ImageMask;

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
	void ColorCursorText();
	TextEditMask* m_textMask;
	ImageMask* m_imageMask;
};

