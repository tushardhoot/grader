#ifndef GRADESQLQUERY_H
#define GRADESQLQUERY_H

#include "Query.h"
#include "CourseGrade.h"
#include <QString>
#include <QDebug>

class CourseSqlQuery :public Query {
	public:
		CourseSqlQuery(QSqlDatabase db = QSqlDatabase());

		bool selectFromCid(const int cid);
		bool selectFromActive(const int active);
		bool insert(QString name, double grade = 0.0, int active = true);
		bool update(int cid, QString name, double grade = 0.0, 
			int active = true, int rec_code = 0);
		bool selectAll();

		operator CourseGrade();
	protected:
		static const QString TABLE;
		static const QString SELECT_ID_ONLY;
		static const QString SELECT_ACTIVE_ONLY;
		static const QString SELECT_ALL;
		static const QString UPDATE;
		static const QString INSERT;
		static const QString FIELDS;
};

#endif