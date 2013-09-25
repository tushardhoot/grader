#include "FormComboBox.h"

FormComboBox::FormComboBox() :FormField() {
}

FormComboBox::FormComboBox(QString label, QComboBox* field, QPushButton* submit)
	:FormField(label,field,submit) {
	FormComboBox::field = field;
}

FormComboBox::~FormComboBox() {
}

FormFieldResult FormComboBox::getFieldContent() const {
	return FormFieldResult(field->currentText());
}

void FormComboBox::setReadOnly(bool readOnly) const {
	FormComboBox::field->setEditable(readOnly);
}

void FormComboBox::setValidator(QValidator* validator) {
	FormComboBox::field->setValidator(validator);
}