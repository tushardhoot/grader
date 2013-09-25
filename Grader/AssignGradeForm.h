#ifndef ASSIGNGRADEFORM_H
#define ASSIGNGRADEFORM_H

#include "Form.h"
#include "AssignmentGrade.h"
#include <QRegExp>
#include <memory>

class AssignGradeForm :public Form {
	Q_OBJECT
	public:
		enum Type { EDITABLE, READONLY };
		AssignGradeForm(Type type, QWidget* parent = (QWidget*)0);
		AssignGradeForm(std::shared_ptr<AssignmentGrade> assignmentGrade, 
			Type type, QWidget* parent = (QWidget*)0);

		void setAssignmentGrade(std::shared_ptr<AssignmentGrade> grade);
		std::shared_ptr<AssignmentGrade>
			getAssignmentGrade() const;
		void setUpdatable();

	protected:
		std::shared_ptr<AssignmentGrade> assignmentGrade;
		void addReadOnlyLineEdit(QString text = "");
		void initForm(Type type);

		FormLineEdit* name;
		FormLineEdit* weight;
		FormLineEdit* score;
		
		static const enum Indices { NAME_IDX, WEIGHT_IDX, SCORE_IDX };

	protected slots:
		void formSubmitted();

	signals:
		void assignSubmitted(std::shared_ptr<AssignmentGrade>); 
		

};

#endif ASSIGNGRADEFORM_H