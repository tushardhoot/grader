#ifndef FORMS_H
#define FORMS_H

#include <QtGui/QWidget>
#include <QtGui/QBoxLayout>
#include <QStringList>
#include <QVector>
#include "FormField.h"
#include "FormFieldResult.h"
#include "FormTextEdit.h"
#include "FormComboBox.h"
#include "FormLineEdit.h"
#include <QDebug>

class Form :public QWidget {
	Q_OBJECT
	public:
		Form(QWidget* parent = (QWidget*)0,QBoxLayout::Direction = QBoxLayout::TopToBottom);	
		virtual ~Form();

		void setButtonText(QString text);
		int addFieldTextEdit(QString label);
		int addFieldComboBox(QString label, QStringList* options);
		int addFieldLineEdit(QString label);
		FormField* getFormField(int index) const;
		void finalize();
	
	protected:
		int addField(FormField* field);
		QVector<FormField*>* fields;
		QVector<FormFieldResult>* results;
		QBoxLayout* layout;
		QPushButton* button;

	public slots:
		void captureResults();

	signals:
		void submitted();
		void resultsCaptured();

};

#endif