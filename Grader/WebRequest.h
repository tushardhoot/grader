#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <QObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QByteArray>
#include <QDebug>
#include <QJson/serializer.h>
#include "Grade.h"

class WebRequest :public QObject {
	Q_OBJECT
	enum RestAction;
	public:
		WebRequest(QNetworkAccessManager* network, 
			Grade* data = new Grade());
		virtual ~WebRequest();

		void send();
		void setNetwork(QNetworkAccessManager* network);
		void setData(Grade* data);
		void setRestAction(const RestAction type = GET);

		enum RestAction { GET, POST, PUT, DELETE };

	protected:
		virtual QUrl getUrl() const = 0;
		Grade* data;
		QNetworkAccessManager* network;
		RestAction restAction;

		virtual QNetworkReply* sendGet() = 0;
		virtual QNetworkReply* sendPost() = 0;
		virtual QNetworkReply* sendPut() = 0;
		virtual QNetworkReply* sendDelete() = 0;

		virtual void processResponse(QNetworkReply* response) = 0;
		QByteArray getJson() const;

};

#endif