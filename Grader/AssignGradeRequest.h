#ifndef ASSIGNGRADEREQUEST_H
#define ASSIGNGRADEREQUEST_H

#include "WebRequest.h"
#include <QDebug>

class AssignGradeRequest :public WebRequest {
	Q_OBJECT
	public:
		AssignGradeRequest(QNetworkAccessManager* network,
			Grade* data = new Grade());
		virtual ~AssignGradeRequest();

	protected:
		virtual QUrl getUrl() const;
		virtual QNetworkReply* sendGet();
		virtual QNetworkReply* sendPost();
		virtual QNetworkReply* sendPut();
		virtual QNetworkReply* sendDelete();

		virtual void processResponse(QNetworkReply* reply);
		QNetworkReply* replya;
};

#endif