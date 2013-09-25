#include "FormField.h"

FormField::FormField() {
	layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
}

FormField::FormField(QString label, QWidget* field, QPushButton* submit) {
	layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
	
	if (label != "") {
		this->label = new QLabel(label);
		layout->addWidget(this->label);
	}
		
	this->field = field;
	this->lastResult = FormFieldResult();

	
	
	layout->addWidget(this->field);
}

FormField::~FormField() {
}

QVariant FormField::lastSubmission() const {
	return lastResult;
}

void FormField::formSubmitted() {
	lastResult = getFieldContent();

	emit submitted();
}


