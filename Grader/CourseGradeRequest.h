#ifndef COURSEGRADEREQUEST_H
#define COURSEGRADEREQUEST_H

#include <QObject>
#include "WebRequest.h"

class CourseGradeRequest :public WebRequest {
	Q_OBJECT
	public:
		CourseGradeRequest(QNetworkAccessManager* network, 
			Grade* data = new Grade());
		virtual ~CourseGradeRequest();

	protected:
		virtual QUrl getUrl() const;
		virtual QNetworkReply* sendGet();
		virtual QNetworkReply* sendPost();
		virtual QNetworkReply* sendPut();
		virtual QNetworkReply* sendDelete();

		virtual void processResponse(QNetworkReply* reply);
};

#endif