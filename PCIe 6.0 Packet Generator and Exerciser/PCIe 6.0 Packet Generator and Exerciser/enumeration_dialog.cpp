#include "enumeration_dialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
PcieEnumerationDialog::PcieEnumerationDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    this->resize(200,150);
    QVBoxLayout* layout = new QVBoxLayout(this);
    messageLabel_ = new QLabel("Enumeration of the PCIe is currently running...", this);
    messageLabel_->setWordWrap(true);

    layout->addWidget(messageLabel_);
    setLayout(layout);
}

void PcieEnumerationDialog::setMessage(QString message) {
	messageLabel_->setText(message);
}