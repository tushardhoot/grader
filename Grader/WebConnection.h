#ifndef WEBCONNECTION_H
#define WEBCONNECTION_H

#include <QObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include "Grade.h"
#include "CourseGrade.h"
#include "CourseGradeRequest.h"
#include "AssignGradeRequest.h"
#include "AssignmentGrade.h"

class WebConnection :public QObject {
	Q_OBJECT
	public:
		WebConnection();
		virtual ~WebConnection();

		CourseGradeRequest* 
			createCourseGradeRequest(CourseGrade* grade = new CourseGrade()) const;
		AssignGradeRequest*
			createAssignGradeRequest(AssignmentGrade* grade = new AssignmentGrade()) const;

	protected:
		QNetworkAccessManager* network;
		
};

#endif