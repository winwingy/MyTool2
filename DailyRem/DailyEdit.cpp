#include "stdafx.h"
#include "DailyEdit.h"
#include "TextEditMask.h"

DailyEdit::DailyEdit(void)
	: m_textMask(new TextEditMask(this))
	, m_maskCover(new QLabel(this))
{
	initialize();
	connection();
}


DailyEdit::~DailyEdit(void)
{

}

void DailyEdit::initialize()
{
	//setFocusProxy(m_maskCover);
	setFocusProxy(m_textMask);

	QPalette pal;
	pal.setColor(QPalette::Base, QColor(255, 0, 0, 0));
	pal.setColor(QPalette::HighlightedText, QColor(0, 255, 0, 50));
	m_maskCover->setPalette(pal);
}

void DailyEdit::connection()
{
	QObject::connect(m_textMask, &TextEditMask::signalFocusIn, [&]()
	{
		//setFocus();
		//setFocus();
	});

// 	QObject::connect(this, &QTextEdit::cursorPositionChanged, [&]()
// 	{
// 		QRect rc = cursorRect();
// 		rc.setRect(0, rc.top(), width(), rc.height());
// 		m_textMask->setClearArea(rc);
// 	});

// 	QObject::connect(this, SIGNAL(cursorPositionChanged()), this, 
// 		SLOT(OnCursorPositionChanged()));
// 
// 	QObject::connect(this, SIGNAL(textChanged()), this, 
// 		SLOT(OnTextChanged()));
}

void DailyEdit::OnTextChanged()
{
	int a = 2;
}

void DailyEdit::OnCursorPositionChanged()
{
	QRect rc = cursorRect();
	rc.setRect(0, rc.top(), width(), rc.height());
	m_textMask->setClearArea(rc);
}

void DailyEdit::resizeEvent(QResizeEvent *e)
{
	const QSize & newSize = e->size();
	m_textMask->setGeometry(0, 0, newSize.width(), newSize.height());
	m_maskCover->setGeometry(00, 0, newSize.width(), newSize.height());

	__super::resizeEvent(e);	
}

void DailyEdit::setMaskText(const QString& text)
{
	std::wstring text1(L"我们者地要人的我工工");
	text1 += text1 += text1 += text1 += text1 += text1;
	m_textMask->setText(QString::fromStdWString(text1));
}
