#pragma once

#include <QDialog>

class QLabel;

class PcieEnumerationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PcieEnumerationDialog(QWidget* parent = nullptr);
    void setMessage(QString message);
public Q_SLOTS:
    
private:
    QLabel* messageLabel_;
};
