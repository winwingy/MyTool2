#include "StdAfx.h"
#include "PassWordDialog.h"



PassWordDialog::PassWordDialog(QWidget* par)
	: QMainWindow(par)
	, m_edit(nullptr)
{
	initialize();
	connection();
}


PassWordDialog::~PassWordDialog(void)
{
}

void PassWordDialog::initialize()
{
	this->setWindowTitle("input password!");
	QWidget* centerWidget = new QWidget(this);
	this->setCentralWidget(centerWidget);

	QHBoxLayout* layout = new QHBoxLayout(centerWidget);
	m_edit = new QLineEdit;
	m_edit->setEchoMode(QLineEdit::Password);
	layout->addWidget(m_edit);
	m_edit->installEventFilter(this);
}

void PassWordDialog::connection()
{


}

void PassWordDialog::eventFilter(QObject *obj, QEvent *ev)
{
	if (obj == m_edit)
	{
		if (ev == Qt::Key_Enter)
		{
			QString text = m_edit->text();
			emit signalPassword(text);
		}
	}
	__super::eventFilter(obj, ev);
}
