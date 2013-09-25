#include "AddCourseDialog.h"

AddCourseDialog::AddCourseDialog(QWidget* parent, Qt::WindowFlags flags) 
	:QInputDialog(parent, flags) {
		setOkButtonText("Create Course!");
		setCancelButtonText("Cancel");
		setLabelText("Name:");
		setInputMode(QInputDialog::TextInput);
}