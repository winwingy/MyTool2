#include "stdafx.h"
#include "DailyMask.h"
#include "qcoreevent.h"
#include "qDebug"
#include "qtextobject.h"
#include "tool\config.h"
#include "DailyType.h"
#include "tool\logWj.h"

DailyMask::DailyMask(QWidget* par)
	: m_level(Level_mask_line)
{
	initialize();
	connection();
}


DailyMask::~DailyMask(void)
{
}


void DailyMask::initialize()
{
	QPalette pl = this->palette();
	pl.setBrush(QPalette::Base,QBrush(QColor(63, 93, 123, 125)));
	pl.setColor(QPalette::Highlight, QColor(0, 0, 0, 0));
	pl.setColor(QPalette::HighlightedText, QColor(0, 0,0, 0));


	this->setPalette(pl);


// 	setWindowFlags(Qt::FramelessWindowHint);
// 	setAttribute(Qt::WA_TranslucentBackground);
	// 所有鼠标键盘操作全部会穿透窗口到下方窗口
	setAttribute(Qt::WA_TransparentForMouseEvents );
	installEventFilter(this);
	setLineWrapMode(QTextEdit::NoWrap);

	
}


void DailyMask::ColorTextByLineB(int lineNumber, int columnNumber)
{
	QTextDocument* textDocument= document();//获取指定textEdit位置
	QTextBlock textBlock = textDocument->findBlockByLineNumber(lineNumber);//通过行号找到指定行 数据块
	QTextCursor cursor(textBlock);

	//bool ret = cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor, 1);
	//bool ret = cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor, 1);
	cursor.select(QTextCursor::LineUnderCursor);
	setTextCursor(cursor);
}


void DailyMask::ColorTextByLine(int lineNumber, int columnNumber)
{
	QTextDocument* textDocument= document();//获取指定textEdit位置
	QTextBlock textBlock = textDocument->findBlockByLineNumber(lineNumber);//通过行号找到指定行 数据块
	QTextCursor cursor(textBlock);
	cursor.setVisualNavigation(true);
	cursor.clearSelection();
	bool ret = false;
	int columnNow = 0;
	int lineNow = 0;

	
	int maskBefore = ConfigWy::GetShared()->GetValue(
		APPKEY, _T("maskBefore"), 20);
	int maskAfter = ConfigWy::GetShared()->GetValue(
		APPKEY, _T("maskAfter"), 10);
	int maskLineBefore= ConfigWy::GetShared()->GetValue(
		APPKEY, _T("maskLineBefore"), 2);
	int maskLineAfter = ConfigWy::GetShared()->GetValue(
		APPKEY, _T("maskLineAfter"), 2);


	if (Level_mask_line == m_level)
	{
		int beginColumn = columnNumber - maskBefore;
		if (beginColumn < 0)
		{	
			ret = cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor,
				-beginColumn);
		}
		else
		{
			ret = cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 
				beginColumn);
		}
		columnNow = cursor.columnNumber();
		ret = cursor.movePosition(QTextCursor::Right, 
			QTextCursor::KeepAnchor, columnNumber + maskAfter);
		columnNow = cursor.columnNumber();
		//cursor.select(QTextCursor::WordUnderCursor);
		this->setTextCursor(cursor);
	}
	else if (Level_mask_threeLine == m_level)
	{
		int upLine = maskLineBefore;
		if (lineNumber < upLine)
			upLine = lineNumber;
	
		ret = cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, upLine);
		lineNow = cursor.blockNumber();
		ret = cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor,
			lineNumber + maskLineAfter);
		lineNow = cursor.blockNumber();
		this->setTextCursor(cursor);
	}
	else if (Level_mask_clear == m_level)
	{
		cursor.select(QTextCursor::Document);
		this->setTextCursor(cursor);		
	}
}

void DailyMask::connection()
{

}

void DailyMask::resizeEvent(QResizeEvent * ev)
{
	__super::resizeEvent(ev);
}

bool DailyMask::eventFilter(QObject *o, QEvent *e)
{
	if (e->type() == QEvent::MouseButtonPress)
	{
		e->ignore();
		return true;
	}
	return __super::eventFilter(o, e);
}

void DailyMask::keyPressEvent(QKeyEvent *e)
{
	// << ("DailyMask");
	__super::keyPressEvent(e);
}

void DailyMask::setMaskLevel(Level_mask level)
{
	if (m_level == level)
		m_level = Level_mask_line;
	else
		m_level = level;
}

void DailyMask::ColorTextByRect(const QRect& rc)
{
	QTextCursor cursor = cursorForPosition(
		QPoint(rc.left() + rc.width()/2, rc.top() + rc.height()/2));

	int lineNumber = cursor.blockNumber();
	int columnNumber = cursor.columnNumber();
	
	TRACE_printf(_T("%d, %d"), lineNumber, columnNumber);

	int maskBefore =  ConfigWy::GetShared()->GetValue(
		APPKEY, _T("maskBefore"), 20);
	int maskAfter = ConfigWy::GetShared()->GetValue(
		APPKEY, _T("maskAfter"), 10);
	int maskLineBefore= ConfigWy::GetShared()->GetValue(
		APPKEY, _T("maskLineBefore"), 2);
	int maskLineAfter = ConfigWy::GetShared()->GetValue(
		APPKEY, _T("maskLineAfter"), 2);

	bool ret = false;
	int columnNow = 0;
	QRect selRect;
	if (Level_mask_line == m_level)
	{
		ret = cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor,
			maskBefore);
		selRect.setTopLeft(cursorRect(cursor).topLeft());
		ret = cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 
			maskBefore + maskAfter);
		selRect.setBottomRight(cursorRect(cursor).bottomRight());
		this->setTextCursor(cursor);
	}
	else if (Level_mask_threeLine == m_level)
	{
		int upLine = maskLineBefore;
		if (lineNumber < upLine)
			upLine = lineNumber;

		ret = cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, upLine);
		int lineNow = cursor.blockNumber();
		ret = cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor,
			lineNumber + maskLineAfter);
		lineNow = cursor.blockNumber();
		this->setTextCursor(cursor);
	}
	else if (Level_mask_clear == m_level)
	{
		cursor.select(QTextCursor::Document);
		this->setTextCursor(cursor);		
	}

	emit signalsSelRectChanged(selRect);
}
