#include "custom_line_edit.h"





using namespace Ui;

 CustomLineEdit::CustomLineEdit(const QString& labelText, int width, int height, const QString& content, QWidget* parent, bool readOnly )
	 : QFrame(parent)
 {
	label = new QLabel(labelText);
    lineEdit = new QLineEdit(content);
    lineEdit->setEnabled(!readOnly);
    lineEdit ->setReadOnly(readOnly);
    layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    setLayout(layout);
    setFixedSize(width, height);
	
}
 

CustomLineEdit::~CustomLineEdit()
{
	
}




