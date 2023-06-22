#pragma once

#include <QDialog>

class QLabel;
class QPushButton;
class PcieEnumerationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PcieEnumerationDialog(QWidget* parent = nullptr);
    void setMessage(QString message);
public Q_SLOTS:
    void onOkButtonClicked();
private:
    QLabel* messageLabel_;
    QPushButton* okButton_;
};
