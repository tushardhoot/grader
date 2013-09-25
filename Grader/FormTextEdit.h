#ifndef FORMTEXTEDIT_H
#define FORMTEXTEDIT_H

#include "FormField.h"
#include <QtGui/QTextEdit>
#include <QString>

class FormTextEdit :public FormField {
	Q_OBJECT
	public:
		FormTextEdit();
		FormTextEdit(QString label, QTextEdit* field, QPushButton* submit);
		virtual ~FormTextEdit();

		virtual void setReadOnly(bool readOnly) const;
		virtual void setValidator(QValidator* validator);

	protected:
		QTextEdit* field;
		virtual FormFieldResult getFieldContent() const;

	private:
		QValidator* validator;

	private slots:
		bool validate();
};

#endif