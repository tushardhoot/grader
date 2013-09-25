#include "ErrorMessage.h"

ErrorMessage::ErrorMessage(QWidget *parent) :QErrorMessage(parent) {
	setModal(true);
}

ErrorMessage::ErrorMessage(QString msg, bool forceQuit) :QErrorMessage() {
	if (forceQuit) {
		QObject::connect(this,SIGNAL(finished(int)),this,SLOT(forceQuit()));
	}

	setModal(true);
	showMessage(msg);
	raise();
}

void ErrorMessage::forceQuit(int returnCode) {
	QApplication::exit(returnCode);
}