#include "enumeration_dialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
PcieEnumerationDialog::PcieEnumerationDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_messageLabel = new QLabel("Enumeration of the PCIe is currently running...", this);
    layout->addWidget(m_messageLabel);
    //close the dialog after 5 seconds
    QTimer::singleShot(5000, this, SLOT(close()));

}