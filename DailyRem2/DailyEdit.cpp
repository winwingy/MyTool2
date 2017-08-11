#include "stdafx.h"
#include "DailyEdit.h"
#include "DailyMask.h"
#include "qboxlayout.h"
#include "qDebug"
#include "qevent.h"
#include "qtimer.h"
#include "qtextlayout.h"
#include "QTextBlock"
#include "MaskBack.h"


DailyEdit::DailyEdit(QWidget* par)
	: QTextEdit(par)
	, m_back(nullptr)
	, m_mask(nullptr)
{
	initialize();
	connection();
	//test();
}

DailyEdit::~DailyEdit(void)
{

}

void DailyEdit::resizeEvent(QResizeEvent * ev)
{
	__super::resizeEvent(ev);
}

void getFileSteam(const QString& filePath, QString* fileStream)
{
	FILE* fp = nullptr;
	_tfopen_s(&fp, filePath.toStdWString().c_str(), _T("rb"));
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fileStream->resize(size);
	fseek(fp, 0, SEEK_SET);
	int readed = fread((char*)fileStream->data(), 1, size, fp);
	*fileStream = QString::fromLocal8Bit((char*)fileStream->data(), readed);
	fclose(fp);
}

void DailyEdit::initialize()
{
// 	QPalette pl = this->palette();
// 	pl.setBrush(QPalette::Base,QBrush(QColor(63, 93, 123, 125)));
// 
// 	this->setPalette(pl);
	m_mask = new DailyMask(this);
	m_back = new MaskBack(this, m_mask);

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(m_back);

	QString fileStream;
	getFileSteam("mask.txt", &fileStream);
	if (fileStream.isEmpty())
	{
		getFileSteam("..\\DailyRem2\\mask.txt", &fileStream);
	}
	fileStream.replace("\r\n", "\0");
	fileStream.replace(" ", "\0");
	fileStream.replace("	", "\0");
	fileStream.replace(QRegExp("[a-zA-Z]"), "\0");
	fileStream.replace(QRegExp("[0-9]"), "\0");
	for (int i = 1; i < 50; ++i)
	{
		fileStream.insert(i*80, "\r\n");
	}
	m_mask->setText(fileStream);

}



void DailyEdit::connection()
{
	QObject::connect(this, &QTextEdit::cursorPositionChanged, [&]()
	{
		int row = 0;
		int column = 0;
		onCursorPositionChanged(&row, &column);
		emit cursorPositionChangedEx(row, column);
	});
}

// void DailyEdit::onCursorPositionChanged(int* row, int* column)
// {
// 	//当前光标
// 	QTextCursor tc = this->textCursor(); 
// 	QTextLayout *pLayout = tc.block().layout();
// 	//当前光标在本BLOCK内的相对位置
// 	int nCurpos = tc.position() - tc.block().position();
// 	int nTextline = pLayout->lineForTextPosition(nCurpos).lineNumber() +
// 		tc.block().firstLineNumber();
// 	//<<"nTextline=" << nTextline<<endl;           //可以看到行号随着光标的改变而改变
// 	*row = nTextline;
// 	*column = nCurpos;
// }

void DailyEdit::onCursorPositionChanged(int* row, int* column)
{
	*row = getCursorLine2(column);
	//m_mask->ColorTextByLine(*row, *column);



	m_mask->ColorTextByRect(cursorRect());
}

void DailyEdit::test()
{
	QString text = QString::fromStdWString(L"我们是工人，, jka  最近接触QTextEdit比较多，想让用户在单击QTextEdit的时候可以选择特定的文本。但查了一下文档没有发现有直AA, jka\r\n");
	text += text + text + text + text + text + text+ text + text + text + text+ text +
		text + text+ text + text + text + text+ text + text + text;
	setText(text);
	m_mask->setText(text);
}

void DailyEdit::onHotKey(QKeyEvent *e)
{
	bool isChange = false;
	if (e->modifiers() == Qt::ControlModifier)
	{
		switch(e->key())
		{
		case Qt::Key_F:
			{
				m_mask->setMaskLevel(DailyMask::Level_mask_threeLine);
				isChange = true;
				break;
			}
		case Qt::Key_G:
			{
				m_mask->setMaskLevel(DailyMask::Level_mask_line);
				isChange = true;
				break;
			}
		case Qt::Key_E:
			{
				m_mask->setMaskLevel(DailyMask::Level_mask_clear);
				isChange = true;
				break;
			}
		}
	}
	if (isChange)
	{
		int columnNumber = 0;
		//int lineNumber = getCursorLine(&columnNumber);
		// << "lineNumber=" << lineNumber << "columnNumber=" << columnNumber;
		//m_mask->ColorTextByLine(lineNumber, columnNumber);

		m_mask->ColorTextByRect(cursorRect());
	}
}


void DailyEdit::keyPressEvent(QKeyEvent *e)
{
	onHotKey(e);

	__super::keyPressEvent(e);
// 	int columnNumber = 0;
// 	int lineNumber = getCursorLine(&columnNumber);
// 	// << "lineNumber=" << lineNumber << "columnNumber=" << columnNumber;
// 	m_mask->ColorTextByLine(lineNumber, columnNumber);
}


bool DailyEdit::eventFilter(QObject *o, QEvent *e)
{
	return __super::eventFilter(o, e);
}

int DailyEdit::getCursorLine(int* column)
{
	QTextDocument*textDocument= document();//获取指定textEdit位置
	//通过textEdit的光标位置得到光标所在行值
	QTextCursor cursor;
	cursor = textCursor();
	cursor.position();
	int lineNumber = cursor.blockNumber();//获取光标所在列用cursor.columnNumber();
	*column = cursor.columnNumber();
	return lineNumber;
}


int DailyEdit::getCursorLine2(int* column)
{
	QTextCursor tc = this->textCursor(); 
	QTextLayout *pLayout = tc.block().layout();
	int nCurpos = tc.position() - tc.block().position();
	int nTextline = pLayout->lineForTextPosition(nCurpos).lineNumber() +
	 	tc.block().firstLineNumber();
	*column = nCurpos;
	return nTextline;
}


void DailyEdit::focusInEvent(QFocusEvent *e)
{
	__super::focusInEvent(e);
// 	int lineNumber = getCursorLine();
// 	// << "lineNumber=" << lineNumber;
}

void DailyEdit::mousePressEvent(QMouseEvent *e)
{
	__super::mousePressEvent(e);	
// 	int columnNumber = 0;
// 	int lineNumber = getCursorLine(&columnNumber);
// 	// << "lineNumber=" << lineNumber << "columnNumber=" << columnNumber;
// 	m_mask->ColorTextByLine(lineNumber, columnNumber);
}
