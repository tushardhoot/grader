#include "databasemanager.h"

bool DatabaseManager::openDB() {
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    #ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("graderdb.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    #else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName("graderdb.sqlite");
    #endif
 
    // Open databasee
    return db.open();
}

QString DatabaseManager::getCoursesTable() {
	static QString TABLE_COURSES = "gr_courses";
	return TABLE_COURSES;
}

QString DatabaseManager::getGradesTable() {
	static QString TABLE_GRADES = "gr_grades";
	return TABLE_GRADES;
}

QSqlError DatabaseManager::lastError() {
    // If opening database has failed user can ask 
    // error description by QSqlError::text()
    return db.lastError();
}
 
void DatabaseManager::closeDB() {
    // Close database
    db.close();
}

DatabaseManager::DatabaseManager(QObject *parent) :QObject(parent) {
}

int DatabaseManager::querySize(QSqlQuery* query) {
	int size = -1;
	if (query->first()) {
		size = 1;
		while (query->next()) {
			size++;
		}
	}

	// Move back to start.
	query->first();
	return size;
}

bool DatabaseManager::transaction() {
	return db.transaction();
}

bool DatabaseManager::commit() {
	return db.commit();
}

bool DatabaseManager::rollback() {
	return db.rollback();
}
