#pragma once

#include <QDialog>

class QLabel;

class PcieEnumerationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PcieEnumerationDialog(QWidget* parent = nullptr);

private:
    QLabel* m_messageLabel;
};
