#ifndef FORMLINEEDIT_H
#define FORMLINEEDIT_H

#include <QtGui/QLineEdit>
#include "FormField.h"

class FormLineEdit :public FormField {
	Q_OBJECT
	public:
		FormLineEdit();
		FormLineEdit(QString label, QLineEdit* field, QPushButton* submit);

		virtual void setReadOnly(bool readOnly) const;
		void setText(QString defaultResult);
		virtual void setValidator(QValidator* validator);
		void setPlaceholderText(QString placeholder);
	protected:
		QLineEdit* field;
		virtual FormFieldResult getFieldContent() const;

	signals:
		void textChanged(const QString&);
		void textEdited(const QString&);
};

#endif