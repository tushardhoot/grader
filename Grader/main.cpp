#include <QtGui/QApplication>
#include <QString>

#include "grader.h"
#include "primaryframe.h"
#include "gradedisplaycoll.h"
#include "gradedisplay.h"

#include <qwidget.h>
#include <qboxlayout.h>

 int main(int argc, char *argv[])
 {
    QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed( true );
	QFile qss("style.qss");
	qss.open(QFile::ReadOnly);
	app.setStyleSheet(qss.readAll());
	qss.close();

	(new Grader())->show();

	return app.exec();
 }