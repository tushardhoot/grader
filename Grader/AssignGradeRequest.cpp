#include "AssignGradeRequest.h"

AssignGradeRequest::AssignGradeRequest(QNetworkAccessManager* network,
	Grade* data) :WebRequest(network, data) {
}

AssignGradeRequest::~AssignGradeRequest() {
}

QUrl AssignGradeRequest::getUrl() const {
	// TODO: Add real URL
	return QUrl("http://localhost/grader/course.php");
}

QNetworkReply* AssignGradeRequest::sendGet() {
	QNetworkRequest request = QNetworkRequest(getUrl());
	return network->get(request);
}

QNetworkReply* AssignGradeRequest::sendPut() {
	QNetworkRequest request = QNetworkRequest(getUrl());
	return network->put(request,getJson());
}

QNetworkReply* AssignGradeRequest::sendPost() {
	QUrl postUrl;
	postUrl.addQueryItem("msg", getJson());
	QNetworkRequest request = QNetworkRequest(getUrl());
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
	return network->post(request,postUrl.encodedQuery());
}

QNetworkReply* AssignGradeRequest::sendDelete() {
	QNetworkRequest request = QNetworkRequest(getUrl());
	return network->deleteResource(request);
}

void AssignGradeRequest::processResponse(QNetworkReply* request) {
	replya = request;
	QObject::connect(request,SIGNAL(finished()),this,SLOT(testFunc()));

}