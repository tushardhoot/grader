#include "AssignSqlQuery.h"

const QString AssignSqlQuery::TABLE = DatabaseManager::getGradesTable();
const QString AssignSqlQuery::FIELDS = "gid,course,name,grade,score,weight,loc_recorded,rem_recorded,rec_code";
const QString AssignSqlQuery::SELECT_ID_ONLY = "SELECT " + FIELDS + " from " + TABLE + " WHERE gid = :gid";
const QString AssignSqlQuery::SELECT_COURSE_ONLY = "SELECT " + FIELDS + " from " + TABLE + " WHERE course = :course";
const QString AssignSqlQuery::UPDATE = "UPDATE " + TABLE + " SET course=:course,name=:name,score=:score,weight=:weight " +
	",loc_recorded=:loc_recorded,rem_recorded=:rem_recorded,rec_code=:rec_code WHERE gid = :gid";
const QString AssignSqlQuery::INSERT = "INSERT INTO " + TABLE + " (course,name,grade,score,weight,loc_recorded) " +
	"VALUES (:course,:name,:grade,:score,:weight,:loc_recorded)";

AssignSqlQuery::AssignSqlQuery(QSqlDatabase db) 
	:Query(db) {
}

AssignSqlQuery::~AssignSqlQuery() {}

bool AssignSqlQuery::selectFromGid(int id) {
	prepare(SELECT_ID_ONLY);
	bindValue(":gid",id);

	return exec();
}

bool AssignSqlQuery::selectFromCourse(int course) {
	prepare(SELECT_COURSE_ONLY);
	bindValue(":course",course);

	return exec();
}

bool AssignSqlQuery::update(int id, int course, QString name, double score, 
	double weight, int loc_rec, int rem_rec, int rec_code) {
	prepare(UPDATE);
	
	bindValue(":gid",id);
	bindValue(":course",course);
	bindValue(":name",name);
	bindValue(":score",score);
	bindValue(":weight",weight);
	bindValue(":loc_recorded",loc_rec);
	bindValue(":rem_recorded",rem_rec);
	bindValue(":rec_code",rec_code);

	return exec();
}

bool AssignSqlQuery::insert(int course, QString name, double score, 
	double weight, int loc_rec) {

	prepare(INSERT);
	bindValue(":course",course);
	bindValue(":name",name);
	bindValue(":score",score);
	bindValue(":weight",weight);
	bindValue(":loc_recorded",loc_rec);

	return exec();
}

AssignSqlQuery::operator AssignmentGrade() {
	if (isValid()) {
		int id = (value(0)).toInt();
		int course = (value(1)).toInt();
		QString name = (value(2)).toString();
		double grade = (value(3)).toDouble();
		double score = (value(4)).toDouble();
		double weight = (value(5)).toDouble();
		int loc_recorded = (value(6)).toInt();
		int rem_recorded = (value(7)).toInt();
		int rec_code = (value(8)).toInt();

		return AssignmentGrade(id,course,name,grade,score,weight,
			loc_recorded,rem_recorded,rec_code);
	} else {
		return AssignmentGrade();
	}
}