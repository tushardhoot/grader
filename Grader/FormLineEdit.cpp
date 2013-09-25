#include "FormLineEdit.h"

FormLineEdit::FormLineEdit() :FormField() {
}

FormLineEdit::FormLineEdit(QString label, QLineEdit* field, QPushButton* submit)
	:FormField(label,field,submit) {
	FormLineEdit::field = field;
	QObject::connect(field,SIGNAL(textChanged(const QString&)),
		this,SIGNAL(textChanged(const QString&)));
	QObject::connect(field,SIGNAL(textEdited(const QString&)),
		this,SIGNAL(textEdited(const QString&)));
}

FormFieldResult FormLineEdit::getFieldContent() const {
	return FormFieldResult(field->text());
}

void FormLineEdit::setReadOnly(bool readOnly) const {
	FormLineEdit::field->setReadOnly(readOnly);

	if (readOnly) {
		FormLineEdit::field->setAutoFillBackground(true);
		QPalette pal = FormLineEdit::field->palette();
		pal.setColor(FormLineEdit::field->backgroundRole(),Qt::gray);
		FormLineEdit::field->setPalette(pal);
	} else {
		FormLineEdit::field->setAutoFillBackground(true);
		QPalette pal = FormLineEdit::field->palette();
		pal.setColor(FormLineEdit::field->backgroundRole(),Qt::white);
		FormLineEdit::field->setPalette(pal);
	}
}

void FormLineEdit::setText(QString defaultResult) {
	FormLineEdit::field->setText(defaultResult);
}

void FormLineEdit::setValidator(QValidator* validator) {
	FormLineEdit::field->setValidator(validator);
}

void FormLineEdit::setPlaceholderText(QString placeholder) {
	FormLineEdit::field->setPlaceholderText(placeholder);
}