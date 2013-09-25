#include "CourseSqlQuery.h"

const QString CourseSqlQuery::TABLE = DatabaseManager::getCoursesTable();
const QString CourseSqlQuery::FIELDS = "cid,name,grade,active,rec_code";
const QString CourseSqlQuery::SELECT_ID_ONLY = "SELECT " + FIELDS + " FROM "
	+ TABLE + " WHERE cid=:cid";
const QString CourseSqlQuery::SELECT_ACTIVE_ONLY = "SELECT " + FIELDS +
	" FROM " + TABLE + " WHERE active=:active";
const QString CourseSqlQuery::SELECT_ALL = "SELECT " + FIELDS + " FROM " +
	TABLE;
const QString CourseSqlQuery::INSERT = "INSERT INTO " + TABLE + " (name," +
	"grade, active) VALUES (:name,:grade,:active)";
const QString CourseSqlQuery::UPDATE = "UPDATE " + TABLE + " SET name=:name" +
	"grade=:grade,active=:active,rec_code=:rec_code WHERE cid=:cid";

CourseSqlQuery::CourseSqlQuery(QSqlDatabase db)
	:Query(db) {
}

bool CourseSqlQuery::selectFromCid(const int cid) {
	prepare(SELECT_ID_ONLY);

	bindValue(":cid", cid);

	return exec();
}

bool CourseSqlQuery::selectFromActive(const int active) {
	prepare(SELECT_ACTIVE_ONLY);

	bindValue(":active", active);

	return exec();
}

bool CourseSqlQuery::insert(QString name, double grade, int active) {
	prepare(INSERT);

	bindValue(":name", name);
	bindValue(":grade", grade);
	bindValue(":active", active);

	return exec();
}

bool CourseSqlQuery::update(int cid, QString name, double grade, 
	int active, int rec_code) {

	prepare(UPDATE);

	bindValue(":cid", cid);
	bindValue(":name", name);
	bindValue(":grade", grade);
	bindValue(":active", active);
	bindValue(":rec_code", rec_code);

	return exec();
}

bool CourseSqlQuery::selectAll() {
	return exec(SELECT_ALL);
}

CourseSqlQuery::operator CourseGrade() {
	if (isValid()) {
		int id = value(0).toInt();
		QString name = value(1).toString();
		double grade = value(2).toDouble();
		bool active = value(3).toBool();
		int rec_code = value(4).toInt();

		return CourseGrade(id,name,active,grade,rec_code);
	} else {
		return CourseGrade();
	}
}

