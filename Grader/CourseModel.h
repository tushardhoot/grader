#ifndef GRADEMODEL_H
#define GRADEMODEL_H

#include "DatabaseModel.h"
#include "CourseSqlQuery.h"
#include "CourseGrade.h"

class CourseModel :public DatabaseModel {
	Q_OBJECT
	public:
		std::shared_ptr<CourseSqlQuery> selectFromCid(const int cid);
		std::shared_ptr<CourseSqlQuery> selectAll();
	public slots:
		bool update(std::shared_ptr<CourseGrade> grade);
		bool insert(std::shared_ptr<CourseGrade> grade);
};

#endif