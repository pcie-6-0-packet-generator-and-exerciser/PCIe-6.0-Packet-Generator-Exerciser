#include "config_space_widget.h"
#include "custom_line_edit.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include "type1_config_space/type1_config.h"

using namespace Ui;

ConfigSpaceWidget::ConfigSpaceWidget(Type1Config* type1space , QWidget* parent)
	: QFrame(parent)
{
	QGridLayout* layout = new QGridLayout;
    int width = 200;
    int height = 60;
	string currentReg;
	int regNum = 0;
	layout->addWidget(new QLabel("000h"), 0, 0,1,1,Qt::AlignRight);

	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Vendor ID", 2 * width, height, QString::fromStdString(currentReg), this), 0, 3, 1, 2);
	boost::to_string(type1space->readType1Reg(regNum++),currentReg);
	layout->addWidget(new CustomLineEdit("Device ID", 2*width, height, QString::fromStdString(currentReg), this), 0, 1, 1, 2);
	

	layout->addWidget(new QLabel("004h"), 1, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Command", 2 * width, height, QString::fromStdString(currentReg), this), 1, 3, 1, 2);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Status", 2*width, height, QString::fromStdString(currentReg), this), 1, 1, 1, 2);
	

	layout->addWidget(new QLabel("008h"), 2, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Revision ID", width, height, QString::fromStdString(currentReg), this), 2, 4, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Class Code", 3*width, height, QString::fromStdString(currentReg), this), 2, 1, 1, 3);
	

	layout->addWidget(new QLabel("00Ch"), 3, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Cache Line Size", width, height, QString::fromStdString(currentReg), this), 3, 4, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Primary Latency Timer", width, height, QString::fromStdString(currentReg), this), 3, 3, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Header Type", width, height, QString::fromStdString(currentReg), this), 3, 2, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("BIST", width, height, QString::fromStdString(currentReg), this), 3, 1, 1, 1);
	

	layout->addWidget(new QLabel("010h"), 4, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("BAR0", 4*width, height, QString::fromStdString(currentReg), this), 4, 1, 1, 4,Qt::AlignCenter);

	layout->addWidget(new QLabel("014h"), 5, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("BAR1", 4*width, height, QString::fromStdString(currentReg), this), 5, 1, 1, 4);

	layout->addWidget(new QLabel("018h"), 6, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Primary Bus Number", width, height, QString::fromStdString(currentReg), this), 6, 4, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Secondary Bus Number", width, height, QString::fromStdString(currentReg), this), 6, 3, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Subordinate Bus Number", width, height, QString::fromStdString(currentReg), this), 6, 2, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Secondary Latency Timer", width, height, QString::fromStdString(currentReg), this), 6, 1, 1, 1);
	

	layout->addWidget(new QLabel("01Ch"), 7, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("IO Base", width, height, QString::fromStdString(currentReg), this), 7, 4, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("IO Limit", width, height, QString::fromStdString(currentReg), this), 7, 3, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Secondary Status", 2*width, height, QString::fromStdString(currentReg), this), 7, 1, 1, 2);

	layout->addWidget(new QLabel("020h"), 8, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Memory Base", 2 * width, height, QString::fromStdString(currentReg), this), 8, 3, 1, 2);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Memory Limit", 2*width, height, QString::fromStdString(currentReg), this), 8, 1, 1, 2);
	

	layout->addWidget(new QLabel("024h"), 9, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Prefetchable Memory Base", 2 * width, height, QString::fromStdString(currentReg), this), 9, 3, 1, 2);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Prefetchable Memory Limit", 2*width, height, QString::fromStdString(currentReg), this), 9, 1, 1, 2);
	

	layout->addWidget(new QLabel("028h"), 10, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Prefetchable Base Upper 32 Bits", 4*width, height, QString::fromStdString(currentReg), this), 10, 1, 1, 4);

	layout->addWidget(new QLabel("02Ch"), 11, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Prefetchable Limit Upper 32 Bits", 4*width, height, QString::fromStdString(currentReg), this), 11, 1, 1, 4);

	layout->addWidget(new QLabel("030h"), 12, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("IO Base Upper 16 Bits", width, height, QString::fromStdString(currentReg), this), 12, 3, 1, 2);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("IO Limit Upper 16 Bits", width, height, QString::fromStdString(currentReg), this), 12, 1, 1, 2);
	
	layout->addWidget(new QLabel("034h"), 13, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Capability Pointer", width, height, QString::fromStdString(currentReg), this), 13, 4, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Reserved", 3*width, height, "", this), 13, 1, 1, 3);
	

	layout->addWidget(new QLabel("038h"), 14, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Expansion ROM Base Address", 4*width, height, QString::fromStdString(currentReg), this), 14, 1, 1, 4);

	layout->addWidget(new QLabel("03Ch"), 15, 0,1,1, Qt::AlignRight);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Interrupt Line", width, height, QString::fromStdString(currentReg), this), 15, 4, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Interrupt Pin", width, height, QString::fromStdString(currentReg), this), 15, 3, 1, 1);
	boost::to_string(type1space->readType1Reg(regNum++), currentReg);
	layout->addWidget(new CustomLineEdit("Bridge Control", 2*width, height, QString::fromStdString(currentReg), this), 15, 1, 1, 2);
	
	

	layout->setSpacing(0);

	setLayout(layout);

    for (int i = 0; i < layout->count(); i++) {
        QHBoxLayout* row = dynamic_cast<QHBoxLayout*>(layout->itemAt(i)->layout());
        if (row) {
            row->setSpacing(0);
        }
    }
}


ConfigSpaceWidget::~ConfigSpaceWidget()
{
} 