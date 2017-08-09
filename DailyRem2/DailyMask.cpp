#include "DailyMask.h"
#include "qcoreevent.h"
#include "qDebug"
#include "qtextobject.h"

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
	pl.setBrush(QPalette::Base,QBrush(QColor(0,0,125,125)));
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
//  	ColorTextByLineB(lineNumber, columnNumber);
//  	return;
//  	QTextDocument* textDocument= document();//获取指定textEdit位置
//  	QTextBlock textBlock = textDocument->findBlockByLineNumber(lineNumber);//通过行号找到指定行 数据块
//  
//  	QTextCursor cursor(textDocument);
//  
//  	QTextCursor highlight_cursor(textDocument);
//  	QTextCharFormat color_format(highlight_cursor.charFormat());
//  	color_format.setForeground(Qt::green);
//  	color_format.setBackground(Qt::red);
// 
// 	selectAll();
//  
//  	cursor.setCharFormat(color_format);



// 	QTextDocument* textDocument= document();
// 	QTextCursor cursor(textDocument);
// 	cursor.setPosition(30, QTextCursor::MoveAnchor);	
// 	cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::MoveAnchor, lineNumber);
// 	cursor.select(QTextCursor::WordUnderCursor);
// 	this->setTextCursor(cursor);
	QTextDocument* textDocument= document();//获取指定textEdit位置
	QTextBlock textBlock = textDocument->findBlockByLineNumber(lineNumber);//通过行号找到指定行 数据块
	QTextCursor cursor(textBlock);
	cursor.setVisualNavigation(true);
	cursor.clearSelection();
	bool ret = false;
	int columnNow = 0;
	int lineNow = 0;
	const int MaskCount = 20;

	if (Level_mask_line == m_level)
	{
		int beginColumn = columnNumber - MaskCount;
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
		ret = cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, MaskCount*2);
		columnNow = cursor.columnNumber();
		//cursor.select(QTextCursor::WordUnderCursor);
		this->setTextCursor(cursor);
	}
	else if (Level_mask_threeLine == m_level)
	{
		const int MutilCount = 2;
		int upLine = MutilCount;
		if (lineNumber < upLine)
			upLine = lineNumber;
	
		ret = cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, upLine);
		lineNow = cursor.blockNumber();
		ret = cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor, MutilCount*2);
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
	qDebug() << ("DailyMask");
	__super::keyPressEvent(e);
}

void DailyMask::setMaskLevel(Level_mask level)
{
// 	if (m_level == level)
// 		m_level = Level_mask_line;
// 	else
		m_level = level;
}
