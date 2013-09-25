#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QErrorMessage>
#include <QApplication>
#include <QSqlQuery>

class DatabaseManager : public QObject {
	Q_OBJECT
    public:
        DatabaseManager(QObject *parent = 0);
        QSqlError lastError();
		static int querySize(QSqlQuery* query);
		bool openDB();
		void closeDB();
		bool transaction();
		bool commit();
		bool rollback();

		static QString getCoursesTable();
		static QString getGradesTable();

    private:
        QSqlDatabase db;
};

#endif