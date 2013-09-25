#include "AssignModel.h"

std::shared_ptr<AssignmentGrade> 
	AssignModel::queryToObject(std::shared_ptr<AssignSqlQuery> query){
	if (query != NULL && query->isValid()) {
		int id = (query->value(0)).toInt();
		int course = (query->value(1)).toInt();
		QString name = (query->value(2)).toString();
		double grade = (query->value(3)).toDouble();
		double score = (query->value(4)).toDouble();
		double weight = (query->value(5)).toDouble();
		int loc_recorded = (query->value(6)).toInt();
		int rem_recorded = (query->value(7)).toInt();
		int rec_code = (query->value(8)).toInt();

		return std::make_shared<AssignmentGrade>
			(id,course,name,grade,score,weight);
	} else {
		return std::make_shared<AssignmentGrade>();
	}
}

bool AssignModel::update(std::shared_ptr<AssignmentGrade> assignmentGrade) {
	
	AssignSqlQuery query = AssignSqlQuery(*this->db);

	int id = assignmentGrade->getId();

	if (id == AssignmentGrade::NO_ID)
		return false;

	int course = assignmentGrade->getCourse();
	QString name = assignmentGrade->getName();
	double score = assignmentGrade->getScore();
	double weight = assignmentGrade->getWeight();
	int loc_recorded = assignmentGrade->getLocRecorded();
	int rem_recorded = assignmentGrade->getRemRecorded();
	int rec_code = assignmentGrade->getRecCode();

	return query.update(id,course,name,score,weight,loc_recorded,
		rem_recorded,rec_code);
}

bool AssignModel::insert(std::shared_ptr<AssignmentGrade> assignmentGrade) {
	AssignSqlQuery query = AssignSqlQuery(*this->db);

	int course = assignmentGrade->getCourse();
	QString name = assignmentGrade->getName();
	double score = assignmentGrade->getScore();
	double weight = assignmentGrade->getWeight();
	int loc_recorded = 1;

	bool result = query.insert(course,name,score,weight,loc_recorded);
	if (result) {
		assignmentGrade->setId(query.lastInsertId().toInt());
	}

	return result;
}