#ifndef QUERY_H
#define QUERY_H

#include <QSqlQuery>
#include <QVariant>
#include "DatabaseManager.h"
#include <QSqlDatabase>

class Query :public QSqlQuery {
	public:
		Query(QSqlDatabase db);
		virtual ~Query();
};

#endif QUERY_H