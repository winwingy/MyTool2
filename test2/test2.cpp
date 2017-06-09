#include "test2.h"
#include "qtextedit.h"

test2::test2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QTextEdit* ed = new QTextEdit(this);
	QObject::connect(ed, SIGNAL(cursorPositionChanged()), this, SLOT(OnCursorPosChanged()));
	ed->setGeometry(rect());
	ed->show();
}

void test2::OnCursorPosChanged()
{
	int a = 1;
}

test2::~test2()
{

}
