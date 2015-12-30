#include "widget2.h"
#include <iostream>
#include <cstdio>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	widget2 *widget = new widget2();
	widget->show();
	return app.exec();
}
