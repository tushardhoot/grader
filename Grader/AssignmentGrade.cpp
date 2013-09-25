#include "AssignmentGrade.h"

AssignmentGrade::AssignmentGrade() :Grade(NO_ID,"",0),score(0),weight(0),
	loc_recorded(0),rem_recorded(0) {	
}

AssignmentGrade::AssignmentGrade(int id, int course, QString name, 
	double score,double weight) :Grade(id,name,score*weight),course(course),
	score(score),weight(weight),loc_recorded(0),rem_recorded(0) {
}

AssignmentGrade::AssignmentGrade(int id, int course, QString name, 
	double grade, double score, double weight, int loc_recorded, 
	int rem_recorded, int rec_code) :Grade(id,name,grade,rec_code),
	course(course),score(score),weight(weight),loc_recorded(loc_recorded),
	rem_recorded(rem_recorded) {
}

AssignmentGrade::AssignmentGrade(const AssignmentGrade& other)
	:Grade(other),course(other.course),score(other.score),weight(other.weight),
	loc_recorded(other.loc_recorded),rem_recorded(other.rem_recorded) {
	
}

AssignmentGrade::~AssignmentGrade() {
}

JsonBuilder AssignmentGrade::toJson() const {
	JsonBuilder result = Grade::toJson();
	result.add(FieldStringMap::course, course);
	result.add(FieldStringMap::score, score);
	result.add(FieldStringMap::weight, weight);
	result.add(FieldStringMap::loc_recorded, loc_recorded);
	result.add(FieldStringMap::rem_recorded, rem_recorded);

	return result;
}


double AssignmentGrade::getScore() const {
	return score;
}

void AssignmentGrade::setScore(double score) {
	this->score = score;
	setGrade(score * weight);
}

double AssignmentGrade::getWeight() const {
	return weight;
}

void AssignmentGrade::setWeight(double weight) {
	this->weight = weight;
	setGrade(score * weight);
}

int AssignmentGrade::getCourse() const {
	return course;
}

void AssignmentGrade::setCourse(int course) {
	this->course = course;
}

int AssignmentGrade::getRemRecorded() const {
	return rem_recorded;
}

void AssignmentGrade::setRemRecorded(int rem_recorded) {
	this->rem_recorded = rem_recorded;
}

int AssignmentGrade::getLocRecorded() const {
	return loc_recorded;
}

void AssignmentGrade::setLocRecorded(int loc_recorded) {
	this->loc_recorded = loc_recorded;
}

