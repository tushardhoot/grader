#ifndef ASSIGNGRADEMODEL_H
#define ASSIGNGRADEMODEL_H

#include "DatabaseModel.h"
#include "QSqlQuery.h"
#include "AssignmentGrade.h"

class AssignGradeModel :public DatabaseModel {
	public:
		AssignGradeModel(QSqlDatabase* db);
		virtual ~AssignGradeModel();

		static AssignmentGrade* queryToObject(QSqlQuery* query) const;

	private:
};

#endif