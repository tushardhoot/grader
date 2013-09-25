#ifndef PRIMARYFRAME_H
#define PRIMARYFRAME_H

#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QComboBox>
#include "CourseModel.h"
#include <QSqlQuery>
#include <QModelIndex>
#include <QObject>
#include "Form.h"
#include "DatabaseManager.h"
#include <qdebug.h>
#include <QVector>
#include "grader.h"
#include "AssignmentGrade.h"
#include "CourseGrade.h"
#include "AssignGradeForm.h"
#include "AssignModel.h"
#include <QVariant>
#include "TabAssignments.h"

class PrimaryFrame : public QTabWidget {
	Q_OBJECT
	public:
		PrimaryFrame(QWidget* parent = 0);
		virtual ~PrimaryFrame();

	protected:
		QBoxLayout* buttonBox;
		QPushButton* addAssButton;
		QPushButton* addCourseButton;

	private:
		void setUpAssignment();

};

#endif