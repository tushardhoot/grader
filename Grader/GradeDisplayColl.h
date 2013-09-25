#ifndef GRADEDISPLAYCOLL_H
#define GRADEDISPLAYCOLL_H

#include "gradedisplay.h"
#include <QtGui/QBoxLayout>
#include <QSize>
#include <memory>
#include "CourseGrade.h"

class GradeDisplayColl : public QWidget {
	Q_OBJECT
	public:
		GradeDisplayColl(QWidget* parent = 0);
		~GradeDisplayColl();

	public slots:
		void newGradeDisplay(std::shared_ptr<CourseGrade> gd);

	signals:
		void gradeDisplayAdded();

	private:
		QBoxLayout* layout;
};

#endif