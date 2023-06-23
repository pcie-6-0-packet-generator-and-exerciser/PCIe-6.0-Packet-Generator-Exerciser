#include "custom_line_edit.h"
#include <QPlainTextEdit>





using namespace Ui;

 CustomLineEdit::CustomLineEdit(const QString& labelText, int width, int height, const QString& content, QWidget* parent, bool readOnly )
	 : QFrame(parent)
 {
	label = new QLabel(labelText);
    lineEdit = new QPlainTextEdit(content);
    lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lineEdit->setEnabled(!readOnly);
    lineEdit ->setReadOnly(readOnly);
    //lineEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //lineEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //lineEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    lineEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    setLayout(layout);
    setFixedSize(width, height);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    //setStyleSheet("QFrame { background-color: rgb(255, 255, 255); border: 1px solid rgb(0, 0, 0); }");
	
}
 

CustomLineEdit::~CustomLineEdit()
{
	delete label;
    delete lineEdit;
    delete layout;
}
void CustomLineEdit::setScrollBarEnabled(bool enabled)
{
    if (enabled)
    {
		lineEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        lineEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        

	}
    
}



