#include "stdafx.h"
#include "DailyEdit.h"
#include "TextEditMask.h"
#include "ImageMask.h"
#include "qtextobject"

DailyEdit::DailyEdit(void)
	: m_textMask(new TextEditMask(this))
	, m_imageMask(new ImageMask(this))
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
	//setFocusProxy(m_textMask);

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

void DailyEdit::ColorCursorText()
{
	QTextDocument*textDocument= document();//��ȡָ��textEditλ��
	//ͨ��textEdit�Ĺ��λ�õõ����������ֵ
	QTextCursor cursor;
	cursor = textCursor();
	int lineNumber = cursor.blockNumber();//��ȡ�����������cursor.columnNumber();
	QTextBlock textBlock = textDocument->findBlockByLineNumber(lineNumber);//ͨ���к��ҵ�ָ���� ���ݿ�
	QString selectLine = textBlock.text();//���õ������ݴ���һ���ַ�����
	m_textMask->ColorTextByLine(lineNumber);
}

void DailyEdit::resizeEvent(QResizeEvent *e)
{
	const QSize & newSize = e->size();
	m_textMask->setGeometry(0, 0, newSize.width(), newSize.height());
	//m_imageMask->setGeometry(0, 0, newSize.width(), newSize.height());

	__super::resizeEvent(e);	
}

void DailyEdit::setMaskText(const QString& text)
{
	std::wstring text1(L"ABC�����ߵ�Ҫ�˵��ҹ���");
	text1 += text1 += text1 += text1 += text1 += text1;
	m_textMask->setText(QString::fromStdWString(text1));
	m_textMask->ColorTextCharFormat(QString::fromStdWString(L"ABC"));
}
