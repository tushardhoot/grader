#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H

#include <QSqlDatabase>
#include <QVariant>
#include <QString>
#include <QObject>
#include <memory>

class DatabaseModel :public QObject {
	Q_OBJECT
	public:
		DatabaseModel(std::shared_ptr<QSqlDatabase> db = 
			std::shared_ptr<QSqlDatabase>(new QSqlDatabase()));

	protected:
		std::shared_ptr<QSqlDatabase> db;
};

#endif