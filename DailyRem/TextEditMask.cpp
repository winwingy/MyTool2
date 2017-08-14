#include "stdafx.h"
#include "TextEditMask.h"


TextEditMask::TextEditMask(QWidget* par)
	: QTextEdit(par)
{
	//setFocusPolicy(Qt::NoFocus);
// 
// 	QPalette pal;
// 	pal.setColor(QPalette::Base, QColor(255, 0, 0, 0));
// 	pal.setColor(QPalette::HighlightedText, QColor(0, 255, 0, 50));
// 	this->setPalette(pal);

	QPalette pl = palette();

	pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));

	setPalette(pl);
	this->setStyleSheet("QTextEdit{border: none;}");
	
}


TextEditMask::~TextEditMask(void)
{
}

void TextEditMask::focusInEvent(QFocusEvent *e)
{
	__super::focusInEvent(e);
	//emit signalFocusIn();
}

void TextEditMask::mousePressEvent(QMouseEvent *e)
{
	__super::mousePressEvent(e);
	//emit signalFocusIn();
}

bool TextEditMask::eventFilter(QObject* o, QEvent* e)
{
	return __super::eventFilter(o, e);

}

void TextEditMask::ColorTextCharFormat(const QString& search_text)
{
	QTextDocument *documentPtr = this->document();
	bool found = false;
	QTextCursor highlight_cursor(documentPtr);
	QTextCursor cursor(documentPtr);

	//开始
	cursor.beginEditBlock();

	QTextCharFormat color_format(highlight_cursor.charFormat());
	color_format.setForeground(Qt::red);
	while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {

		//查找指定的文本，匹配整个单词
		highlight_cursor = documentPtr->find(search_text, 
			highlight_cursor, QTextDocument::FindCaseSensitively);
		if (!highlight_cursor.isNull()) {
			if(!found)
				found = true;
			highlight_cursor.mergeCharFormat(color_format);
		}
	}
	cursor.endEditBlock();
}

void TextEditMask::paintEvent(QPaintEvent *e)
{	
// 	QPainter painter(this);
// 	//painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
// 	//painter.setPen(Qt::NoPen);
// 	painter.setBrush(Qt::yellow);
// 	painter.drawRect(m_clearArea);
// 	painter.drawText(100, 100, "TextEditMask::paintEvent(QPaintEvent *e)");
	__super::paintEvent(e);
// 	QPainter 
// 	QPainter painter(this);
// 	painter.pix

}

void TextEditMask::setClearArea(const QRect& rc)
{
	m_clearArea = rc;
	update();
}


void TextEditMask::ColorTextByLine(int lineNumber)
{
// 	QTextDocument* textDocument= document();//获取指定textEdit位置
// 	QTextBlock textBlock = textDocument->findBlockByLineNumber(lineNumber);//通过行号找到指定行 数据块
// 	
// 	QTextCursor cursor(textBlock);
// 
// 	QTextCursor highlight_cursor(textDocument);
// 	QTextCharFormat color_format(highlight_cursor.charFormat());
// 	color_format.setForeground(Qt::green);
// 
// 	cursor.mergeCharFormat(color_format);
}

// void TextEditMask::ColorTextByLine(int lineNumber)
// {
//    	QTextDocument*textDocument= document();//获取指定textEdit位置
//    	QTextBlock textBlock = textDocument->findBlockByLineNumber(lineNumber);//通过行号找到指定行 数据块
//    	//textBlock.
//    	
//   
//    
//    
//    	cursor.setPosition(blocks[idx].position());
//    	int pos = blocks[idx].position() + line.textStart() + line.textLength() - 1;
//    	cursor.setPosition(pos,  QTextCursor::KeepAnchor);
//    	QTextCharFormat fmt;
//    	fmt.setFontLetterSpacing(percentOfSpacing);
//    	cursor.mergeCharFormat(fmt);
//    
//    
//    
//    	QTextCursor highlight_cursor(documentPtr);
//    	QTextCursor cursor(documentPtr);
//    
//    	//开始
//    	cursor.beginEditBlock();
//    
//    	QTextCharFormat color_format(highlight_cursor.charFormat());
//    	color_format.setForeground(Qt::red);
//    	while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
//    
//    		//查找指定的文本，匹配整个单词
//    		highlight_cursor = documentPtr->find(search_text, 
//    			highlight_cursor, QTextDocument::FindCaseSensitively);
//    		if (!highlight_cursor.isNull()) {
//    			if(!found)
//    				found = true;
//    			highlight_cursor.mergeCharFormat(color_format);
//    		}
//    	}
//    	cursor.endEditBlock();
// }
