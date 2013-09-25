#include "WebRequest.h"

WebRequest::WebRequest(QNetworkAccessManager* network, Grade* data)
	:QObject() {
	this->network = network;
	this->data = data;
	this->restAction = GET;
}

WebRequest::~WebRequest() {
}

void WebRequest::setData(Grade* data) {
	this->data = data;
}

void WebRequest::setNetwork(QNetworkAccessManager* network) {
	this->network = network;
}

void WebRequest::setRestAction(const RestAction type) {
	this->restAction = type;
}

QByteArray WebRequest::getJson() const {
	if (this->data == NULL) {
		return NULL;
	}

	return this->data->toJson().build().toUtf8();
}

void WebRequest::send() {
	QNetworkReply* response;
	switch(restAction) {
		case PUT:
			response = sendPut();
			break;
		case POST:
			response = sendPost();
			break;
		case DELETE:
			response = sendDelete();
		case GET:
		default:
			response = sendGet();
			break;
	}
	
	processResponse(response);
}