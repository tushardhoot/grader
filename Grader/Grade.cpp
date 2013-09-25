#include "grade.h"

Grade::Grade() :id(NO_ID),name(""),grade(0.0),rec_code(0) {}

Grade::Grade(int id, QString name, double grade, int rec_code) 
	  :id(id),name(name),grade(grade),rec_code(rec_code) {
}

Grade::~Grade() {
}

Grade::Grade(const Grade& gradeObj)
	:id(gradeObj.id),name(gradeObj.name),grade(gradeObj.grade),
	rec_code(gradeObj.rec_code) {
}

JsonBuilder Grade::toJson() const {
	JsonBuilder result;
	result.add(FieldStringMap::id, id);
	result.add(FieldStringMap::name, name);
	result.add(FieldStringMap::grade, grade);
	result.add(FieldStringMap::rec_code, rec_code);

	return result;
}

int Grade::getId() const {
	return id;
}

void Grade::setId(int id) {
	this->id = id;
}

QString Grade::getName() const {
	return name;
}

void Grade::setName(QString name) {
	this->name = name;
}

double Grade::getGrade() const {
	return grade;
}

void Grade::setGrade(double grade) {
	this->grade = grade;

	emit gradeChanged(grade);
}

int Grade::getRecCode() const {
	return rec_code;
}

void Grade::setRecCode(int rec_code) {
	this->rec_code = rec_code;
}