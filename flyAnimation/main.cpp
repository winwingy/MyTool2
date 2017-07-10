#include "stdafx.h"
#include "flyanimation.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	flyAnimation w;
	w.show();
	return a.exec();
}
