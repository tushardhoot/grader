#include "grader.h"

WebConnection* Grader::webConnection = new WebConnection();

Grader::Grader(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), 
	gradeDisplayLayout(new QBoxLayout(QBoxLayout::LeftToRight)) {
	loadDb();
	setUpUi();
}

void Grader::setUpUi() {
	QWidget* window = new QWidget();
	QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, window);

	CourseModel courseModel = CourseModel();
	std::shared_ptr<CourseSqlQuery> query = courseModel.selectAll();
	while(query->next()) {
		CourseGrade grade = static_cast<CourseGrade>(*query);
		addGradeDisplay(std::make_shared<CourseGrade>(*query));
	}

	layout->addLayout(gradeDisplayLayout);

	TabAssignments* assignmentTab = new TabAssignments();
	assignmentTab->setSizePolicy(QSizePolicy::Expanding,
		QSizePolicy::Expanding);

	connect(assignmentTab, SIGNAL(courseCreated(std::shared_ptr<CourseGrade>)),
		this, SLOT(courseCreated(std::shared_ptr<CourseGrade>)));
	connect(assignmentTab, SIGNAL(courseChanged(std::shared_ptr<CourseGrade>)),
		this, SLOT(courseChanged(std::shared_ptr<CourseGrade>)));

	layout->addWidget(assignmentTab, 0, Qt::AlignTop);
	layout->setSpacing(0);
	setCentralWidget(window);
}

void Grader::loadDb() {
	dbm = std::make_shared<DatabaseManager>(this);
	if(!dbm->openDB()) {
		ErrorMessage* errMsg = new ErrorMessage(tr("Error opening database!"),true);
	} else {
		if (!setUpDb()) {
			ErrorMessage* errMsg = new ErrorMessage(tr("Error creating database!"),true);
		}
	}
}

bool Grader::setUpDb() {
	dbm->transaction();
	QSqlQuery query;
	
	// gr_courses
	query.exec("CREATE TABLE IF NOT EXISTS " + DatabaseManager::getCoursesTable() + 
		          " (cid INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT, " + 
				  "grade REAL DEFAULT 0.00, active INTEGER DEFAULT 1, rec_code INTEGER DEFAULT 0);");
	query.clear();

	// gr_grades
	query.exec("CREATE TABLE IF NOT EXISTS " + DatabaseManager::getGradesTable() + 
		          " (gid INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, course INTEGER " +
				  "NOT NULL REFERENCES " + DatabaseManager::getCoursesTable() + "(cid), " + 
				  "name TEXT, grade REAL DEFAULT 0.00, score REAL DEFAULT 0.00, weight REAL DEFAULT 0.00," +
				  "loc_recorded INTEGER DEFAULT 0, rem_recorded INTEGER DEFAULT 0, rec_code INTEGER DEFAULT 0);");
	query.clear();

	// grades triggers
	// insert trigger
	query.exec("CREATE TRIGGER IF NOT EXISTS gr_grades_insert AFTER INSERT ON " + DatabaseManager::getGradesTable() +
			   " FOR EACH ROW WHEN new.loc_recorded = 1 " +
			   "BEGIN " +
			   "UPDATE " + DatabaseManager::getGradesTable() + " SET grade = new.weight * new.score WHERE gid = new.gid;" +
			   "UPDATE " + DatabaseManager::getCoursesTable() + " SET grade = (SELECT SUM(" + DatabaseManager::getGradesTable() + ".grade) FROM " + 
			   DatabaseManager::getGradesTable() + " WHERE course = new.course) WHERE cid = new.course;" +
			   "END");
	query.clear();

	// update trigger
	query.exec("CREATE TRIGGER IF NOT EXISTS gr_grades_update AFTER UPDATE ON " + DatabaseManager::getGradesTable() + 
		       " FOR EACH ROW " +
			   "BEGIN " +
			   "UPDATE " + DatabaseManager::getGradesTable() + " SET grade = new.weight * new.score WHERE gid = new.gid;" + 
			   "UPDATE " + DatabaseManager::getCoursesTable() + " SET grade = (SELECT SUM(" + DatabaseManager::getGradesTable() + ".grade) FROM " + 
			   DatabaseManager::getGradesTable() + " WHERE course = new.course) WHERE cid = new.course;" +
			   "END");
	query.clear();

	// delete trigger
	query.exec("CREATE TRIGGER IF NOT EXISTS gr_grades_delete AFTER DELETE ON " + DatabaseManager::getGradesTable() + 
		       " FOR EACH ROW " +
			   "BEGIN " +
			   "UPDATE " + DatabaseManager::getCoursesTable() + " SET grade = (SELECT SUM(" + DatabaseManager::getGradesTable() + ".grade) FROM " + 
			   DatabaseManager::getGradesTable() + " WHERE course = old.course) WHERE cid = old.course;" +
			   "END");
	query.clear();

	if (dbm->commit()) {
		return true;
	} else {
		dbm->rollback();
		return false;
	}
}

void Grader::courseCreated(std::shared_ptr<CourseGrade> grade) {
	addGradeDisplay(grade);
}

void Grader::addGradeDisplay(std::shared_ptr<CourseGrade> grade) {
	GradeDisplay* gradeDisplay = new GradeDisplay(grade);
	gradeDisplayLayout->addWidget(gradeDisplay);
	gradeDisplays.push_back(gradeDisplay);
}

void Grader::courseChanged(std::shared_ptr<CourseGrade> grade) {
	QVector<GradeDisplay*>::iterator it;
	it = std::find_if(gradeDisplays.begin(), gradeDisplays.end(), 
		[&grade](GradeDisplay*& gd) { 
			return gd->getGrade()->getId() == grade->getId();
	    });

	if (it != gradeDisplays.end()) {
		(*it)->gradeChanged(grade->getGrade());
	}
}