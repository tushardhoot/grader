#include "PrimaryFrame.h"

PrimaryFrame::PrimaryFrame(QWidget* parent) :QTabWidget(parent)	{
		
}

void PrimaryFrame::setUpAssignment() {
	addTab(new TabAssignments(), "Assignments");
}

PrimaryFrame::~PrimaryFrame() {
}