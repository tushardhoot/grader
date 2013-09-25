#ifndef GRADE_H
#define GRADE_H

#include <QString>
#include <QVariantMap>
#include "FieldStringMap.h"
#include <QObject>
#include "JsonBuilder.h"

class Grade :public QObject {
	Q_OBJECT
	public:
		Grade();
		Grade(int id, QString name, double grade = 0.0, int rec_code = 0);
		Grade(const Grade& gradeObj);
		virtual ~Grade();

		virtual JsonBuilder toJson() const;

		virtual int getId() const;
		virtual void setId(int id);

		virtual QString getName() const;
		virtual void setName(QString name);

		virtual double getGrade() const;
		virtual void setGrade(double grade);

		virtual int getRecCode() const;
		virtual void setRecCode(int rec_code);

		static const int NO_ID = 0;

	signals:
		void gradeChanged(double);

	protected:
		int id;
		QString name;
		double grade;
		int rec_code;
};

#endif