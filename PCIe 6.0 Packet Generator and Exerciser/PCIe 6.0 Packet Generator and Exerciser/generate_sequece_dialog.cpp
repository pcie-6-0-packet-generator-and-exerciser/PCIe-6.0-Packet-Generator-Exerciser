#include "generate_sequece_dialog.h"
#include <QBoxLayout>
#include <QLabel>

GenerateSequenceDialog::GenerateSequenceDialog(QWidget* parent) :
    QDialog(parent),
    tlpTypeComboBox_(new QComboBox),
    sequenceLengthLineEdit_(new QLineEdit),
    sequenceTypeComboBox_(new QComboBox),
    initialValueLineEdit_(new QLineEdit),
    stepSizeLineEdit_(new QLineEdit),
    layout_(new QVBoxLayout),
    sequenceLengthValidator_(new QIntValidator(0, 10000, this)),
    initialValueValidator_(new QIntValidator(0, 10000, this)),
    stepSizeValidator_(new QIntValidator(0, 10000, this))
{
    tlpTypeComboBox_->addItem("Memory Read 32b");
    tlpTypeComboBox_->addItem("Memory Read 64b");
    tlpTypeComboBox_->addItem("Memory Write 32b");
    tlpTypeComboBox_->addItem("Memory Write 64b");

    connect(tlpTypeComboBox_, &QComboBox::currentTextChanged, this, &GenerateSequenceDialog::onTlpTypeChanged);
    connect(sequenceTypeComboBox_, &QComboBox::currentTextChanged, this, &GenerateSequenceDialog::onSequenceTypeChanged);
    sequenceLengthLineEdit_->setValidator(sequenceLengthValidator_);

    sequenceTypeComboBox_->addItem("Incremental");
    sequenceTypeComboBox_->addItem("Decremental");
    sequenceTypeComboBox_->addItem("Random");
    sequenceTypeComboBox_->setEnabled(false);
    initialValueLineEdit_->setValidator(initialValueValidator_);
    initialValueLineEdit_->setEnabled(false);
    stepSizeLineEdit_->setValidator(stepSizeValidator_);
    stepSizeLineEdit_->setEnabled(false);
    submitButton_ = new QPushButton("Submit");
    manageLayout();
    connect(this, &QDialog::accepted, this, &GenerateSequenceDialog::onAccepted);
}

GenerateSequenceDialog::~GenerateSequenceDialog()
{
    delete tlpTypeComboBox_;
    delete sequenceLengthLineEdit_;
    delete sequenceTypeComboBox_;
    delete initialValueLineEdit_;
    delete stepSizeLineEdit_;
    delete layout_;
    delete sequenceLengthValidator_;
    delete initialValueValidator_;
    delete stepSizeValidator_;

}

void GenerateSequenceDialog::manageLayout() {

    layout_ = new QVBoxLayout;
    QHBoxLayout* tlpTypeLayout = new QHBoxLayout;
    QLabel* tlpTypeLabel = new QLabel("TLPs Type: ");
    tlpTypeLayout->addWidget(tlpTypeLabel);
    tlpTypeLayout->addWidget(tlpTypeComboBox_);
    layout_->addLayout(tlpTypeLayout);

    QHBoxLayout* sequenceLengthLayout = new QHBoxLayout;
    QLabel* sequenceLengthLabel = new QLabel("Sequence Length: ");
    sequenceLengthLayout->addWidget(sequenceLengthLabel);
    sequenceLengthLayout->addWidget(sequenceLengthLineEdit_);
    layout_->addLayout(sequenceLengthLayout);

    sequenceTypeLayout_ = new QHBoxLayout;
    QLabel* sequenceTypeLabel = new QLabel("Sequence Type: ");
    sequenceTypeLayout_->addWidget(sequenceTypeLabel);
    sequenceTypeLayout_->addWidget(sequenceTypeComboBox_);
    layout_->addLayout(sequenceTypeLayout_);

    QHBoxLayout* initialValueLayout = new QHBoxLayout;
    QLabel* initialValueLabel = new QLabel("Initial Value: ");
    initialValueLayout->addWidget(initialValueLabel);
    initialValueLayout->addWidget(initialValueLineEdit_);
    layout_->addLayout(initialValueLayout);

    QHBoxLayout* stepSizeLayout = new QHBoxLayout;
    QLabel* stepSizeLabel = new QLabel("Step Size: ");
    stepSizeLayout->addWidget(stepSizeLabel);
    stepSizeLayout->addWidget(stepSizeLineEdit_);

    layout_->addLayout(stepSizeLayout);

    layout_->addWidget(submitButton_);

    setLayout(layout_);
}
void GenerateSequenceDialog::onAccepted()
{
    QString tlpType = tlpTypeComboBox_->currentText();
    int sequenceLength = sequenceLengthLineEdit_->text().toInt();
    QString sequenceType = sequenceTypeComboBox_->currentText();
    int initialValue = initialValueLineEdit_->text().toInt();
    int stepSize = stepSizeLineEdit_->text().toInt();

    // Add your logic to handle the TLP sequence here
}

void GenerateSequenceDialog::onTlpTypeChanged() {
    //check tlpTypeComboBox_
    if(tlpTypeComboBox_->currentText() == "Memory Write 32b" || tlpTypeComboBox_->currentText() == "Memory Write 64b") {
        sequenceTypeComboBox_->setEnabled(true);
        initialValueLineEdit_->setEnabled(true);
        stepSizeLineEdit_->setEnabled(true);
	}
    else {
        sequenceTypeComboBox_->setEnabled(false);
        initialValueLineEdit_->setEnabled(false);
        stepSizeLineEdit_->setEnabled(false);
    }
}

void GenerateSequenceDialog::onSequenceTypeChanged() {
	//check sequenceTypeComboBox_
    if (sequenceTypeComboBox_->currentText() == "Random") {
		initialValueLineEdit_->setEnabled(false);
		stepSizeLineEdit_->setEnabled(false);
	}
    else {
		initialValueLineEdit_->setEnabled(true);
		stepSizeLineEdit_->setEnabled(true);
	}
}
