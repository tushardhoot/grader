#ifndef FORMFIELD_H
#define FORMFIELD_H

#include <QObject>
#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include "FormFieldResult.h"
#include <QVariant>
#include <QtGui/QBoxLayout>
#include <QDebug>
#include <QtGui/QValidator>

class FormField :public QWidget {
	Q_OBJECT
	public:
		FormField();
		FormField(QString label, QWidget* field, QPushButton* submit);
		virtual ~FormField();
		
		FormFieldResult lastSubmission() const;
		virtual void setReadOnly(bool readOnly) const = 0;
		virtual void setValidator(QValidator* validator) = 0;

	protected:
		QWidget* field;
		QLabel* label;
		FormFieldResult lastResult;
		QBoxLayout* layout;
		virtual FormFieldResult getFieldContent() const = 0;

	public slots:
		virtual void formSubmitted();

	signals:
		void submitted();
};

#endif