#include "AssignGradeForm.h"

AssignGradeForm::AssignGradeForm(AssignGradeForm::Type type, QWidget* parent)
	:Form(parent, QBoxLayout::LeftToRight) {
	initForm(type);
	setAssignmentGrade(std::make_shared<AssignmentGrade>());
}

AssignGradeForm::AssignGradeForm(std::shared_ptr<AssignmentGrade> assignmentGrade,
							AssignGradeForm::Type type, QWidget* parent)
	:Form(parent, QBoxLayout::LeftToRight) {
	
	initForm(type);
	setAssignmentGrade(assignmentGrade);
}

void AssignGradeForm::setAssignmentGrade(
	std::shared_ptr<AssignmentGrade> assignmentGrade) {
	this->assignmentGrade = assignmentGrade;

	if (assignmentGrade->getLocRecorded()) {
		name->setText(assignmentGrade->getName());
		score->setText(QString::number(assignmentGrade->getScore()));
		weight->setText(QString::number(assignmentGrade->getWeight() * 100));
	}
}

std::shared_ptr<AssignmentGrade> AssignGradeForm::getAssignmentGrade() const {
	return assignmentGrade;
}

void AssignGradeForm::initForm(Type type) {
	QObject::connect(this,SIGNAL(resultsCaptured()),
		this,SLOT(formSubmitted()));

	addFieldLineEdit(""); // name
	addFieldLineEdit(""); // weight
	addFieldLineEdit(""); // score

	name = static_cast<FormLineEdit*>(fields->at(NAME_IDX));
	weight = static_cast<FormLineEdit*>(fields->at(WEIGHT_IDX));
	score = static_cast<FormLineEdit*>(fields->at(SCORE_IDX));

	name->setPlaceholderText(tr("Assignment Name"));
	weight->setPlaceholderText(tr("Value/Weight (as a percentage)"));
	score->setPlaceholderText(tr("Mark"));

	score->setValidator(new QDoubleValidator());
	weight->setValidator(new QDoubleValidator());

	if (type == EDITABLE) {
		setButtonText("Add");
	} else if (type == READONLY) {
		setUpdatable();
	}

	finalize();
}

void AssignGradeForm::setUpdatable() {
	FormLineEdit* fieldName = static_cast<FormLineEdit*>(name);
	FormLineEdit* fieldWeight = static_cast<FormLineEdit*>(weight);
	fieldName->setReadOnly(true);
	fieldWeight->setReadOnly(true);

	setButtonText("Update");
}

void AssignGradeForm::addReadOnlyLineEdit(QString text) {
	int index = addFieldLineEdit("");
	FormLineEdit* field = static_cast<FormLineEdit*>(fields->at(index));
	field->setReadOnly(true);
	field->setText(text);
}

void AssignGradeForm::formSubmitted() {
	assignmentGrade->setName(results->at(NAME_IDX).toString());
	assignmentGrade->setWeight(results->at(WEIGHT_IDX).toDouble()/100);
	assignmentGrade->setScore(results->at(SCORE_IDX).toDouble());

	emit assignSubmitted(assignmentGrade);
}