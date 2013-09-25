#ifndef ASSIGNMENTGRADE_H
#define ASSIGNMENTGRADE_H

#include "grade.h"
#include <QString>

class AssignmentGrade :public Grade {
	Q_OBJECT
	public:
		AssignmentGrade();
		AssignmentGrade(int id, int course, QString name, double marks, 
			double weight);
		AssignmentGrade(int id, int course, QString name, double grade, 
			double marks, double weight, int loc_recorded = 0, 
			int rem_recorded = 0, int rec_code = 0);
		AssignmentGrade(const AssignmentGrade& other);
		virtual JsonBuilder toJson() const;

		virtual ~AssignmentGrade();

		double getWeight() const;
		void setWeight(double weight);

		double getScore() const;
		void setScore(double score);

		int getCourse() const;
		void setCourse(int course);

		int getLocRecorded() const;
		void setLocRecorded(int loc_recorded);

		int getRemRecorded() const;
		void setRemRecorded(int rem_recorded);

	protected:
		double weight;
		double score;
		int course;
		int loc_recorded;
		int rem_recorded;
};

#endif