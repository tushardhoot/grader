#include "FormTextEdit.h"

FormTextEdit::FormTextEdit() :FormField() {
}

FormTextEdit::FormTextEdit(QString label, QTextEdit* field, QPushButton* submit)
	:FormField(label,field,submit) {
	FormTextEdit::field = field;
}

FormTextEdit::~FormTextEdit() {
}

FormFieldResult FormTextEdit::getFieldContent() const {
	return FormFieldResult(field->toPlainText());
}

void FormTextEdit::setReadOnly(bool readOnly) const {
	FormTextEdit::field->setReadOnly(readOnly);

	if (readOnly) {
		FormTextEdit::field->setAutoFillBackground(true);
		QPalette pal = FormTextEdit::field->palette();
		pal.setColor(FormTextEdit::field->backgroundRole(),Qt::gray);
		FormTextEdit::field->setPalette(pal);
	} else {
		FormTextEdit::field->setAutoFillBackground(true);
		QPalette pal = FormTextEdit::field->palette();
		pal.setColor(FormTextEdit::field->backgroundRole(),Qt::white);
		FormTextEdit::field->setPalette(pal);
	}
}

void FormTextEdit::setValidator(QValidator* validator) {
	this->validator = validator;
	QObject::connect(FormTextEdit::field,SIGNAL(textChanged()),this,SLOT(validate())); 
}

bool FormTextEdit::validate() {
	int placeholder = 0;
	if(validator->validate(FormTextEdit::field->toPlainText(),placeholder) != QValidator::Acceptable) {
		// TODO: add validation
		return false;
	} else {
		return true;
	}
}