#include "DailyEdit.h"
#include "DailyMask.h"
#include "qboxlayout.h"
#include "qDebug"
#include "qevent.h"
#include "qtimer.h"
#include "qtextlayout.h"
#include "QTextBlock"


DailyEdit::DailyEdit(QWidget* par)
	: QTextEdit(par)
	, m_mask(new DailyMask(this))
{
	initialize();
	connection();
	test();
}

DailyEdit::~DailyEdit(void)
{

}

void DailyEdit::resizeEvent(QResizeEvent * ev)
{
	__super::resizeEvent(ev);
}

void DailyEdit::initialize()
{
	QPalette pl = this->palette();

	pl.setBrush(QPalette::Base,QBrush(QColor(0,125,0,125)));

	this->setPalette(pl);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(m_mask);
}

void DailyEdit::connection()
{
	QObject::connect(this, &QTextEdit::cursorPositionChanged, [&]()
	{
		onCursorPositionChanged();
	});
}

void DailyEdit::onCursorPositionChanged()
{
	//��ǰ���
	QTextCursor tc = this->textCursor(); 
	QTextLayout *pLayout = tc.block().layout();
	//��ǰ����ڱ�BLOCK�ڵ����λ��
	int nCurpos = tc.position() - tc.block().position();
	int nTextline = pLayout->lineForTextPosition(nCurpos).lineNumber() +
		tc.block().firstLineNumber();
	qDebug()<<"nTextline=" << nTextline<<endl;           //���Կ����к����Ź��ĸı���ı�
}

void DailyEdit::test()
{
	QString text = QString::fromStdWString(L"�����ǹ��ˣ�, jka  ����Ӵ�QTextEdit�Ƚ϶࣬�����û��ڵ���QTextEdit��ʱ�����ѡ���ض����ı���������һ���ĵ�û�з�����ֱAA, jka\r\n");
	text += text + text + text + text + text + text+ text + text + text + text+ text +
		text + text+ text + text + text + text+ text + text + text;
	setText(text);
	m_mask->setText(text);
}

void DailyEdit::onHotKey(QKeyEvent *e)
{
	if (e->modifiers() == Qt::ControlModifier)
	{
		switch(e->key())
		{
		case Qt::Key_F:
			{
				m_mask->setMaskLevel(DailyMask::Level_mask_threeLine);
				break;
			}
		case Qt::Key_G:
			{
				m_mask->setMaskLevel(DailyMask::Level_mask_line);
				break;
			}
		case Qt::Key_E:
			{
				m_mask->setMaskLevel(DailyMask::Level_mask_clear);
				break;
			}
		}
	}
}


void DailyEdit::keyPressEvent(QKeyEvent *e)
{
	onHotKey(e);

	__super::keyPressEvent(e);
	static QTimer* timer = new QTimer(this);
	timer->setInterval(1);
	timer->setSingleShot(true);
	QObject::connect(timer, &QTimer::timeout, [&](){
		int columnNumber = 0;
		int lineNumber = getCursorLine(&columnNumber);
		qDebug() << "lineNumber=" << lineNumber << "columnNumber=" << columnNumber;
		m_mask->ColorTextByLine(lineNumber, columnNumber);
	});
	timer->start();
}


bool DailyEdit::eventFilter(QObject *o, QEvent *e)
{
	return __super::eventFilter(o, e);
}

int DailyEdit::getCursorLine(int* column)
{
	QTextDocument*textDocument= document();//��ȡָ��textEditλ��
	//ͨ��textEdit�Ĺ��λ�õõ����������ֵ
	QTextCursor cursor;
	cursor = textCursor();
	cursor.position();
	int lineNumber = cursor.blockNumber();//��ȡ�����������cursor.columnNumber();
	*column = cursor.columnNumber();
	return lineNumber;
}

void DailyEdit::focusInEvent(QFocusEvent *e)
{
	__super::focusInEvent(e);
// 	int lineNumber = getCursorLine();
// 	qDebug() << "lineNumber=" << lineNumber;
}

void DailyEdit::mousePressEvent(QMouseEvent *e)
{
	__super::mousePressEvent(e);
	static QTimer* timer = new QTimer(this);
	timer->setInterval(1);
	timer->setSingleShot(true);
	QObject::connect(timer, &QTimer::timeout, [&](){
		int columnNumber = 0;
		int lineNumber = getCursorLine(&columnNumber);
		qDebug() << "lineNumber=" << lineNumber << "columnNumber=" << columnNumber;
		m_mask->ColorTextByLine(lineNumber, columnNumber);
	});
	timer->start();
}
