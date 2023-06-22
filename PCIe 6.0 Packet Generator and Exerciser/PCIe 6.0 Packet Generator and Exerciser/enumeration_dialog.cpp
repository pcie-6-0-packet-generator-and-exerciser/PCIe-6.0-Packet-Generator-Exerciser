#include "enumeration_dialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QPushButton>

PcieEnumerationDialog::PcieEnumerationDialog(QWidget* parent)
    : QDialog(parent)
{
    okButton_ = new QPushButton("Ok", this);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    this->resize(200,150);
    QVBoxLayout* layout = new QVBoxLayout(this);
    messageLabel_ = new QLabel("Enumeration of the PCIe is currently running...", this);
    messageLabel_->setWordWrap(true);

    layout->addWidget(messageLabel_);
    layout->addWidget(okButton_);
    setLayout(layout);
    
    connect(okButton_, &QPushButton::clicked, this, &PcieEnumerationDialog::onOkButtonClicked);
}

void PcieEnumerationDialog::setMessage(QString message) {
	messageLabel_->setText(message);
}

void PcieEnumerationDialog::onOkButtonClicked() {
	this->close();
}