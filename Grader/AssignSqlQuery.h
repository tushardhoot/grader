#ifndef ASSIGNSQLQUERY_H
#define ASSIGNSQLQUERY_H

#include "Query.h"
#include "AssignmentGrade.h"
#include <QString>
#include <QDebug>

class AssignSqlQuery :public Query {
	public:
		AssignSqlQuery(QSqlDatabase db = QSqlDatabase());
		virtual ~AssignSqlQuery();

		bool selectFromGid(int id);
		bool selectFromCourse(int id);
		bool update(int id, int course, QString name, double score = 0.0, 
			double weight = 0.0, int loc_rec = 0, int rem_rec = 0, 
			int rec_code = 0);
		bool insert(int course, QString name, double score = 0.0, 
			double weight = 0.0, int loc_rec = 0);

		operator AssignmentGrade();

	protected:
		static const QString TABLE;
		static const QString SELECT_ID_ONLY;
		static const QString SELECT_COURSE_ONLY;
		static const QString UPDATE;
		static const QString INSERT;
		static const QString FIELDS;
		
};

#endif