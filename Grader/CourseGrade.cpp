#include "CourseGrade.h"

CourseGrade::CourseGrade()
	:Grade(),active(true) {}

CourseGrade::
	CourseGrade(int id, QString name, bool active, double grade, int rec_code)
	:Grade(id,name,grade,rec_code),active(active) {
}

CourseGrade::CourseGrade(const CourseGrade& gradeObj) 
	:Grade(gradeObj),active(gradeObj.active) {
}

JsonBuilder CourseGrade::toJson() const {
	JsonBuilder result = Grade::toJson();
	result.add(FieldStringMap::active, active);

	return result;
}

bool CourseGrade::getActive() const {
	return active;
}

void CourseGrade::setActive(bool active) {
	this->active = active;
}