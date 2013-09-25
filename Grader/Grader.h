#ifndef GRADER_H
#define GRADER_H

#include <QtGui/QMainWindow>
#include <QtGui/QScrollArea>
#include <QtSql>
#include <QtGui/QGridLayout>
#include "gradedisplay.h"
#include "primaryframe.h"
#include "ErrorMessage.h"
#include <QDebug>
#include "DatabaseManager.h"
#include "WebConnection.h"
#include <memory>
#include <algorithm>

class Grader : public QMainWindow {
	Q_OBJECT
	public:
		Grader(QWidget *parent = 0, Qt::WFlags flags = 0);

		static WebConnection* webConnection;

	public slots:
		void courseCreated(std::shared_ptr<CourseGrade> grade);
		void courseChanged(std::shared_ptr<CourseGrade> grade);

	private:
		void setUpUi();
		void loadDb();
		bool setUpDb();
		void addGradeDisplay(std::shared_ptr<CourseGrade> grade);


		std::shared_ptr<DatabaseManager> dbm;
		QVector<GradeDisplay*> gradeDisplays;
		QBoxLayout* gradeDisplayLayout;
};

#endif
