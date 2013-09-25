#include "CourseGradeRequest.h"

CourseGradeRequest::CourseGradeRequest(QNetworkAccessManager* network,
	Grade* data) :WebRequest(network,data) {

}

CourseGradeRequest::~CourseGradeRequest() {
}

QNetworkReply* CourseGradeRequest::sendGet() {
	QNetworkRequest request = QNetworkRequest(getUrl());
	return network->get(request);
}

QNetworkReply* CourseGradeRequest::sendPut() {
	QNetworkRequest request = QNetworkRequest(getUrl());
	return network->put(request,getJson());
}

QNetworkReply* CourseGradeRequest::sendPost() {
	QNetworkRequest request = QNetworkRequest(getUrl());
	return network->post(request,getJson());
}

QNetworkReply* CourseGradeRequest::sendDelete() {
	QNetworkRequest request = QNetworkRequest(getUrl());
	return network->deleteResource(request);
}

QUrl CourseGradeRequest::getUrl() const {
	return QUrl("http://google.com");
}

void CourseGradeRequest::processResponse(QNetworkReply* reply) {
}