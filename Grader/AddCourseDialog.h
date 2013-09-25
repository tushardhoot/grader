#ifndef ADDCOURSEDIALOG_H
#define ADDCOURSEDIALOG_H

#include <QtGui/QInputDialog>
#include "Form.h"

class AddCourseDialog : public QInputDialog {
	Q_OBJECT
	public:
		AddCourseDialog(QWidget* parent = 0, Qt::WindowFlags flags = 0);
};

#endif