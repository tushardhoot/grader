#ifndef TABASSIGNMENTS_H
#define TABASSIGNMENTS_H

#include <QtGui/QWidget>
#include <QtGui/QComboBox>
#include <QtGui/QPushButton>
#include <QVariant>
#include "AssignGradeForm.h"
#include <QVector>
#include "CourseGrade.h"
#include "AssignmentGrade.h"
#include "CourseSqlQuery.h"
#include "AssignSqlQuery.h"
#include "CourseModel.h"
#include "AssignModel.h"
#include <QDebug>
#include "AddCourseDialog.h"
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <memory>

class TabAssignments : public QWidget {
	Q_OBJECT
	public:
		TabAssignments(QWidget* parent = 0);

	private:
		QBoxLayout* layout;
		QVector<AssignGradeForm*>* forms;
		QComboBox* mlist;
		QLabel* label;
		QPushButton newCourseButton;
		std::unique_ptr<AssignModel> assignModel;
		std::unique_ptr<CourseModel> courseModel;

		void createCourse(const QString& name);
		void refreshList();
		void blankAssignmentForm(CourseGrade& course,
			AssignGradeForm* oldForm = nullptr);

	public slots:
		void comboBoxChanged(int index);
		void addCourse();
		void assignmentChanged(std::shared_ptr<AssignmentGrade> grade);
		void assignmentCreated(std::shared_ptr<AssignmentGrade> grade);

	signals:
		void courseCreated(std::shared_ptr<CourseGrade>);
		void courseChanged(std::shared_ptr<CourseGrade>);

};

#endif