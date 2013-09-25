#include "TabAssignments.h"

TabAssignments::TabAssignments(QWidget* parent) 
	:QWidget(parent), layout(new QBoxLayout(QBoxLayout::TopToBottom)),
     forms(new QVector<AssignGradeForm*>()), label(new QLabel()),
	 mlist(new QComboBox()), newCourseButton("Add Course", this),
     assignModel(new AssignModel()), courseModel(new CourseModel()) {

	layout->setSpacing(0);

	refreshList();
	mlist->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));

	QObject::connect(mlist,SIGNAL(currentIndexChanged(int)),
		this, SLOT(comboBoxChanged(int)));
	QObject::connect(&newCourseButton, SIGNAL(clicked()), this,
		SLOT(addCourse()));

	label->setText("Course:");
	label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

	newCourseButton.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
	QBoxLayout* mainBox = new QBoxLayout(QBoxLayout::TopToBottom, this);
	QBoxLayout* courseBox = new QBoxLayout(QBoxLayout::LeftToRight);
	courseBox->addWidget(label);
	courseBox->addWidget(mlist);
	courseBox->addWidget(&newCourseButton);

	QLabel* assignmentNameLabel = new QLabel(tr("Name"));
	assignmentNameLabel->setAlignment(Qt::AlignCenter);
	QLabel* assignmentWeightLabel = new QLabel(tr("Value (as % of final mark)"));
	QLabel* assignmentMarkLabel = new QLabel(tr("Mark (out of 100)"));

	QBoxLayout* labelBox = new QBoxLayout(QBoxLayout::LeftToRight);
	labelBox->addWidget(assignmentNameLabel);
	labelBox->addWidget(assignmentWeightLabel);
	labelBox->addWidget(assignmentMarkLabel);

	QFrame* line = new QFrame();
	line->setObjectName(QString::fromUtf8("line"));
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);


	mainBox->addLayout(courseBox);
	mainBox->addLayout(labelBox);
	mainBox->addWidget(line);
	mainBox->addLayout(layout);
	layout->setAlignment(Qt::AlignTop);

	mlist->setCurrentIndex(0);
}

void TabAssignments::comboBoxChanged(int index) {
	QVector<AssignGradeForm*>::iterator it = forms->begin();
	qDebug() << "start forms size " << forms->size();
	while (it != forms->end()) {
		layout->removeWidget(*it);
		(*it)->setParent(0);
		it = forms->erase(it);
	}

	CourseGrade course = mlist->itemData(index).value<CourseGrade>();
	AssignSqlQuery* query = new AssignSqlQuery();
	query->selectFromCourse(course.getId());

	qDebug() << "before loop combobox";
	while(query->next()) {
		std::shared_ptr<AssignmentGrade> assignmentGrade = 
			std::make_shared<AssignmentGrade>(*query);
		AssignGradeForm* assignGradeForm = 
			new AssignGradeForm(assignmentGrade,AssignGradeForm::READONLY, this);

		QObject::connect(assignGradeForm,
			SIGNAL(assignSubmitted(std::shared_ptr<AssignmentGrade>)), 
			assignModel.get(), SLOT(update(std::shared_ptr<AssignmentGrade>)));
		QObject::connect(assignGradeForm,
			SIGNAL(assignSubmitted(std::shared_ptr<AssignmentGrade>)), 
			this, SLOT(assignmentChanged(std::shared_ptr<AssignmentGrade>)));

		forms->push_back(assignGradeForm);
		layout->addWidget(assignGradeForm);
	}

	blankAssignmentForm(course);
}

void TabAssignments::addCourse() {
	AddCourseDialog dialog(this);
	QDialog::DialogCode response = 
		static_cast<QDialog::DialogCode>(dialog.exec());
	if (response == QDialog::Accepted) {
		createCourse(dialog.textValue());
	}
}

void TabAssignments::createCourse(const QString& name) {
	std::shared_ptr<CourseGrade> newCourse =
		std::make_shared<CourseGrade>();
	newCourse->setName(name);
	newCourse->setGrade(0);
	courseModel->insert(newCourse);
	mlist->addItem(newCourse->getName(),
		QVariant::fromValue<CourseGrade>(*newCourse));
	mlist->setCurrentIndex(mlist->count()-1);
	
	emit courseCreated(newCourse);
}

void TabAssignments::refreshList() {
	mlist->clear();
	std::shared_ptr<CourseSqlQuery> courseQuery = courseModel->selectAll();
	
	int currentIndex = 0;
	while (courseQuery->next()) {
		CourseGrade grade = *courseQuery;
		mlist->addItem(grade.getName(),
			QVariant::fromValue<CourseGrade>(grade));
	}
}

void TabAssignments::assignmentChanged(std::shared_ptr<AssignmentGrade> grade) {
	std::shared_ptr<CourseSqlQuery> query = 
		courseModel->selectFromCid(grade->getCourse());

	if (query->next()) {
		emit courseChanged(std::make_shared<CourseGrade>(*query));
	}
}

void TabAssignments::assignmentCreated(std::shared_ptr<AssignmentGrade> grade) {
	std::shared_ptr<CourseSqlQuery> query = 
		courseModel->selectFromCid(grade->getCourse());

	if (query->next()) {
		emit courseChanged(std::make_shared<CourseGrade>(*query));
	}

	blankAssignmentForm(static_cast<CourseGrade>(*query), 
		static_cast<AssignGradeForm*>(sender()));
}

void TabAssignments::blankAssignmentForm
	(CourseGrade& course, AssignGradeForm* oldForm) {
	std::shared_ptr<AssignmentGrade> newAssignGrade = 
		std::make_shared<AssignmentGrade>();

	newAssignGrade->setCourse(course.getId());
	AssignGradeForm* newAssignForm = 
		new AssignGradeForm(newAssignGrade,AssignGradeForm::EDITABLE, this);
	QObject::connect(newAssignForm, 
		SIGNAL(assignSubmitted(std::shared_ptr<AssignmentGrade>)), 
		assignModel.get(), SLOT(insert(std::shared_ptr<AssignmentGrade>)));
	QObject::connect(newAssignForm, 
		SIGNAL(assignSubmitted(std::shared_ptr<AssignmentGrade>)),
		this, SLOT(assignmentCreated(std::shared_ptr<AssignmentGrade>)));

	if (oldForm) {
		oldForm->setUpdatable();
		QObject::disconnect(oldForm, 
			SIGNAL(assignSubmitted(std::shared_ptr<AssignmentGrade>)), 
			this, SLOT(assignmentCreated(std::shared_ptr<AssignmentGrade>)));
		QObject::disconnect(oldForm, 
			SIGNAL(assignSubmitted(std::shared_ptr<AssignmentGrade>)), 
			assignModel.get(), SLOT(insert(std::shared_ptr<AssignmentGrade>)));
		QObject::connect(oldForm,
			SIGNAL(assignSubmitted(std::shared_ptr<AssignmentGrade>)), 
			assignModel.get(), SLOT(update(std::shared_ptr<AssignmentGrade>)));
		QObject::connect(oldForm,
			SIGNAL(assignSubmitted(std::shared_ptr<AssignmentGrade>)),
			this, SLOT(assignmentChanged(std::shared_ptr<AssignmentGrade>)));
	}

    forms->push_back(newAssignForm);
	layout->addWidget(newAssignForm);
}