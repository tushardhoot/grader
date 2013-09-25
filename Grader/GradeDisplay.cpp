#include "GradeDisplay.h"

GradeDisplay::GradeDisplay(std::shared_ptr<CourseGrade> grade, 
	QWidget* parent) :QWidget(parent), grade(grade) {

	QObject::connect(grade.get(), SIGNAL(gradeChanged(double)), 
		this, SLOT(gradeChanged(double)));

	layout = new QVBoxLayout(this);

	disp = new QLabel();
	QFont font = disp->font();
	font.setPointSize(20);
	disp->setFont(font);
	disp->setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	gradeChanged(grade->getGrade());
	layout->addWidget(disp);
	
	label = new QLabel();
	label->setText(grade->getName());
	
	layout->addWidget(label);
}

void GradeDisplay::gradeChanged(double newGrade) {
	disp->setText(QString::number(newGrade));

	if (newGrade > GradeDisplay::PASS) {
		disp->setObjectName("gdPass");
	} else if (newGrade > GradeDisplay::COND) {
		disp->setObjectName("gdCond");
	} else {
		disp->setObjectName("gdFail");
	}

	disp->style()->unpolish(disp);
	disp->style()->polish(disp);
}

void GradeDisplay::setGrade(std::shared_ptr<CourseGrade> grade) {
	this->grade = grade;
}

std::shared_ptr<CourseGrade> GradeDisplay::getGrade() const {
	return grade;
}