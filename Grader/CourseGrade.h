#ifndef COURSEGRADE_H
#define COURSEGRADE_H

#include "grade.h"
#include <QString>
#include <QMetaType>

class CourseGrade :public Grade {
	public:
		CourseGrade();
		CourseGrade(int id, QString name, bool active = true, 
			double grade = 0.0,	int rec_code = 0);
		CourseGrade(const CourseGrade& gradeObj);
		virtual JsonBuilder toJson() const;

		bool getActive() const;
		void setActive(bool active);

	protected:
		bool active;
};

Q_DECLARE_METATYPE(CourseGrade);
#endif