#include "Form.h"

Form::Form(QWidget* parent,QBoxLayout::Direction dir) :QWidget(parent) {
	layout = new QBoxLayout(dir,this);
	fields = new QVector<FormField*>();
	results = new QVector<FormFieldResult>();
	button = new QPushButton();

	QObject::connect(button,SIGNAL(clicked(bool)),this,SLOT(captureResults()));
}

Form::~Form() {
	delete fields;
}

void Form::setButtonText(QString test) {
	button->setText(test);
}

int Form::addField(FormField* field) {
	QObject::connect(this,SIGNAL(submitted()),field,SLOT(formSubmitted()),Qt::DirectConnection);
	fields->push_back(field);
	layout->addWidget(field);

	return fields->size()-1;
}

int Form::addFieldTextEdit(QString label) {
	QTextEdit* textEdit = new QTextEdit();
	FormTextEdit* fTextEdit = new FormTextEdit(label,textEdit,button);
	return addField(fTextEdit);
}

int Form::addFieldComboBox(QString label, QStringList* options) {
	QComboBox* comboBox = new QComboBox();
	comboBox->addItems(*options);
	FormComboBox* fComboBox = new FormComboBox(label,comboBox,button);
	return addField(fComboBox);
}

int Form::addFieldLineEdit(QString label) {
	QLineEdit* lineEdit = new QLineEdit();
	FormLineEdit* fLineEdit = new FormLineEdit(label,lineEdit,button);
	return addField(fLineEdit);
}

FormField* Form::getFormField(int index) const {
	return fields->at(index);
}

void Form::finalize() {
	layout->addWidget(button);
	show();
}

void Form::captureResults() {
	emit submitted();
	results->clear();

	QVector<FormField*>::iterator it;
	for (it = fields->begin(); it != fields->end(); it++) {
		results->push_back((*it)->lastSubmission());
	}

	emit resultsCaptured();
}