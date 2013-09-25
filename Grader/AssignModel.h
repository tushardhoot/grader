#ifndef ASSIGNMODEL_H
#define ASSIGNMODEL_H

#include "DatabaseModel.h"
#include "AssignmentGrade.h"
#include "AssignSqlQuery.h"
#include <QDebug>

class AssignModel :public DatabaseModel {
	Q_OBJECT
	public:
		static std::shared_ptr<AssignmentGrade>
			queryToObject(std::shared_ptr<AssignSqlQuery> query);
	public slots:
		bool update(std::shared_ptr<AssignmentGrade> assignmentGrade);
		bool insert(std::shared_ptr<AssignmentGrade> assignmentGrade);
};

#endif