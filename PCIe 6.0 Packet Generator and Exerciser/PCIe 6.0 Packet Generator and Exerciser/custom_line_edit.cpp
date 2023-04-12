#include "custom_line_edit.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <Qtwidgets/QLineEdit>




using namespace Ui;

CustomLineEdit::CustomLineEdit(QWidget* parent, QString text, int width, int height)
{
	QVBoxLayout* layout = new QVBoxLayout(parent);

	QLabel* label = new QLabel(text, parent);
	layout->addWidget(label);

	lineEdit = new QLineEdit(parent);
	lineEdit->setFixedSize(width, height);
	layout->addWidget(lineEdit);
	
}

CustomLineEdit::~CustomLineEdit()
{
	
}