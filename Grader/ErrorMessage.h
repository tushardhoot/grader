#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QErrorMessage>
#include <QString>
#include <QWidget>
#include <QObject>
#include <QApplication>

class ErrorMessage : public QErrorMessage {
	Q_OBJECT
	public: 
		ErrorMessage(QWidget *parent = 0);
		ErrorMessage(QString msg, bool forceQuit = false);
	private slots:
		void forceQuit(int returnCode = 0);
};

#endif