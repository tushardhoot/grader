#include "GradeDisplayColl.h"

GradeDisplayColl::GradeDisplayColl(QWidget* parent) 
	:QWidget(parent), layout(new QHBoxLayout(this)) {
	layout->setSpacing(2);
	setLayout(layout);
}

GradeDisplayColl::~GradeDisplayColl() {
}

void GradeDisplayColl::newGradeDisplay(std::shared_ptr<CourseGrade> gd) {
	layout->addWidget(new GradeDisplay(gd, this));
	emit gradeDisplayAdded();
}