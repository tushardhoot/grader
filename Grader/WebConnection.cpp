#include "WebConnection.h"

WebConnection::WebConnection() :QObject() {
	network = new QNetworkAccessManager();
}

WebConnection::~WebConnection() {
	delete network;
}

CourseGradeRequest* WebConnection::
	createCourseGradeRequest(CourseGrade* grade) const {
	return new CourseGradeRequest(network, grade);
}

AssignGradeRequest* WebConnection::
	createAssignGradeRequest(AssignmentGrade* grade) const {
		return new AssignGradeRequest(network, grade);
}





