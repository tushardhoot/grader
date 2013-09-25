#ifndef FORMCOMBOBOX_H
#define FORMCOMBOBOX_H

#include "FormField.h"
#include <QtGui/QComboBox>
#include <QString>

class FormComboBox :public FormField {
	public:
		FormComboBox();
		FormComboBox(QString label, QComboBox* field, QPushButton* submit);
		virtual ~FormComboBox();

		virtual void setReadOnly(bool readOnly) const;
		virtual void setValidator(QValidator* validator);
	protected:
		QComboBox* field;
		virtual FormFieldResult getFieldContent() const;
};

#endif