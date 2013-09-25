#include "CourseModel.h"

bool CourseModel::insert(std::shared_ptr<CourseGrade> grade) {
	CourseSqlQuery query = CourseSqlQuery(*db);

	QString name = grade->getName();
	double dGrade = grade->getGrade();
	bool active = grade->getActive();

	bool result = query.insert(name, dGrade, active);
	qDebug() << "error " << query.lastError();
	if (result) {
		grade->setId(query.lastInsertId().toInt());
	}

	return result;
}

bool CourseModel::update(std::shared_ptr<CourseGrade> grade) {
	CourseSqlQuery query = CourseSqlQuery(*db);

	int id = grade->getId();
	if (id == Grade::NO_ID)
		return false;

	QString name = grade->getName();
	double dGrade = grade->getGrade();
	bool active = grade->getActive();
	int rec_code = grade->getRecCode();

	return query.update(id, name, dGrade, active, rec_code);
}

std::shared_ptr<CourseSqlQuery> CourseModel::selectAll() {
	std::shared_ptr<CourseSqlQuery> query =
		std::make_shared<CourseSqlQuery>(*db);
	query->selectAll();
	
	return query;
}

std::shared_ptr<CourseSqlQuery> CourseModel::selectFromCid(const int cid) {
	std::shared_ptr<CourseSqlQuery> query = 
		std::make_shared<CourseSqlQuery>(*db);
	query->selectFromCid(cid);

	return query;
}