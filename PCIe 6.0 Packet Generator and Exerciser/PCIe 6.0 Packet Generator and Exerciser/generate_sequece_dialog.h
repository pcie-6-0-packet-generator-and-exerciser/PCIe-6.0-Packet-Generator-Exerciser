#pragma once
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QPushButton>

class GenerateSequenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateSequenceDialog(QWidget* parent = nullptr);
    ~GenerateSequenceDialog();
    int getTlpType() const { return tlpTypeComboBox_->currentIndex(); }
    int getSequenceLength() const { return sequenceLengthLineEdit_->text().toInt(); }
    int getSequenceType() const { return sequenceTypeComboBox_->currentIndex(); }
    int getInitialValue() const { return initialValueLineEdit_->text().toInt(); }
    int getStepSize() const { return stepSizeLineEdit_->text().toInt(); }

private:
    void manageLayout();
public:
    QPushButton* submitButton_;
private:
    QComboBox* tlpTypeComboBox_;
    QLineEdit* sequenceLengthLineEdit_;
    QComboBox* sequenceTypeComboBox_;
    QLineEdit* initialValueLineEdit_;
    QLineEdit* stepSizeLineEdit_;
    QHBoxLayout* sequenceTypeLayout_;
    QVBoxLayout* layout_;
    QIntValidator* sequenceLengthValidator_;
    QIntValidator* initialValueValidator_;
    QIntValidator* stepSizeValidator_;
private slots:
    void onAccepted();
    void onTlpTypeChanged();

};