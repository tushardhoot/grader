#ifndef GRADEDISPLAY_H
#define GRADEDISPLAY_H

#include <QtGui/QWidget>
#include <QtGui/QStyle>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLCDNumber>
#include <QSize>
#include <QtGui/QPalette>
#include <QtGui/QLabel>
#include <QObject>
#include "CourseGrade.h"
#include <memory>

class GradeDisplay : public QWidget {
	Q_OBJECT
	public:
		GradeDisplay(std::shared_ptr<CourseGrade> grade, 
			QWidget* parent = 0);
		std::shared_ptr<CourseGrade> getGrade() const;
		void setGrade(std::shared_ptr<CourseGrade> grade);
	public slots:
		void gradeChanged(double newGrade);
	private:
		std::shared_ptr<CourseGrade> grade;
		QVBoxLayout* layout;
		QLabel* disp;
		QLabel* label;
		enum GradePoints { PASS=60, COND=50, FAIL=0 };
};

#endif