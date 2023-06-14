#include "config_space_widget.h"
#include "custom_line_edit.h"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFormLayout>
using namespace Ui;

ConfigSpaceWidget::ConfigSpaceWidget(QWidget* parent)
    : QFrame(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    int width = 200;
    int height = 50;
    
    QHBoxLayout* row1 = new QHBoxLayout();
    row1->addWidget(new QLabel("000h"));
    row1->addWidget(new CustomLineEdit("Device ID", 2*width, height, "0x10EE", this));
    row1->addWidget(new CustomLineEdit("Vendor ID", 2*width, height, "0x10EE", this));
    layout->addLayout(row1);

    QHBoxLayout* row2 = new QHBoxLayout();
    row2->addWidget(new QLabel("004h"));
    row2->addWidget(new CustomLineEdit("Status", 2*width, height, "0x0000", this));
    row2->addWidget(new CustomLineEdit("Command", 2*width, height, "0x0000", this));
    layout->addLayout(row2);

    QHBoxLayout* row3 = new QHBoxLayout();
    row3->addWidget(new QLabel("008h"));
    row3->addWidget(new CustomLineEdit("Class Code", 3*width, height, "0x060400", this));
    row3->addWidget(new CustomLineEdit("Revision ID", 1*width, height, "0x00", this));
    layout->addLayout(row3);

    QHBoxLayout* row4 = new QHBoxLayout();
    row4->addWidget(new QLabel("00Ch"));
    row4->addWidget(new CustomLineEdit("BIST", width, height, "0x00", this));
    row4->addWidget(new CustomLineEdit("Header Type", width, height, "0x00", this));
    row4->addWidget(new CustomLineEdit("Primary Latency Timer", width, height, "0x00", this));
    row4->addWidget(new CustomLineEdit("Cache Line Size", width, height, "0x00", this));
    layout->addLayout(row4);

    QHBoxLayout* row5 = new QHBoxLayout();
    row5->addWidget(new QLabel("010h"));
    row5->addWidget(new CustomLineEdit("BAR0", 4*width, height, "0x00000000", this), 0, Qt::AlignCenter);
    layout->addLayout(row5);

    QHBoxLayout* row6 = new QHBoxLayout();
    row6->addWidget(new QLabel("014h"));
    row6->addWidget(new CustomLineEdit("BAR1", 4*width, height, "0x00000000", this));
    layout->addLayout(row6);

    QHBoxLayout* row7 = new QHBoxLayout();
    row7->addWidget(new QLabel("018h"));
    row7->addWidget(new CustomLineEdit("Secondary Latency Timer", width, height, "0x00000000", this));
    row7->addWidget(new CustomLineEdit("Subordinate Bus Number", width, height, "0x00000000", this));
    row7->addWidget(new CustomLineEdit("Secondary Bus Number", width, height, "0x00000000", this));
    row7->addWidget(new CustomLineEdit("Primary Bus Number", width, height, "0x00000000", this));
    layout->addLayout(row7);

    QHBoxLayout* row8 = new QHBoxLayout();
    row8->addWidget(new QLabel("01Ch"));
    row8->addWidget(new CustomLineEdit("Secondary Status", 2*width, height, "0x00000000", this));
    row8->addWidget(new CustomLineEdit("IO Limit", width, height, "0x00000000", this));
    row8->addWidget(new CustomLineEdit("IO Base", width, height, "0x00000000", this));
    layout->addLayout(row8);

    QHBoxLayout* row9 = new QHBoxLayout();
    row9->addWidget(new QLabel("020h"));
    row9->addWidget(new CustomLineEdit("Memory Limit", 2*width, height, "0x00000000", this));
    row9->addWidget(new CustomLineEdit("Memory Base", 2*width, height, "0x00000000", this));
    layout->addLayout(row9);

    QHBoxLayout* row10 = new QHBoxLayout();
    row10->addWidget(new QLabel("024h"));
    row10->addWidget(new CustomLineEdit("Prefetchable Memory Limit", 2*width, height, "0x00000000", this));
    row10->addWidget(new CustomLineEdit("Prefetchable Memory Base", 2*width, height, "0x00000000", this));
    layout->addLayout(row10);

    QHBoxLayout* row11 = new QHBoxLayout();
    row11->addWidget(new QLabel("028h"));
    row11->addWidget(new CustomLineEdit("Prefetchable Base Upper 32 Bits", 4*width, height, "0x00000000", this));
    layout->addLayout(row11);

    QHBoxLayout* row12 = new QHBoxLayout();
    row12->addWidget(new QLabel("02Ch"));
    row12->addWidget(new CustomLineEdit("Prefetchable Limit Upper 32 Bits", 4*width, height, "0x00000000", this));
    layout->addLayout(row12);

    QHBoxLayout* row13 = new QHBoxLayout();
    row13->addWidget(new QLabel("030h"));
    row13->addWidget(new CustomLineEdit("IO Limit Upper 16 Bits", 2*width, height, "0x00000000", this));
    row13->addWidget(new CustomLineEdit("IO Base Upper 16 Bits", 2*width, height, "0x00000000", this));
    layout->addLayout(row13);

    QHBoxLayout* row14 = new QHBoxLayout();
    row14->addWidget(new QLabel("034h"));
    row14->addWidget(new CustomLineEdit("Reserved", 3*width, height, "", this));
    row14->addWidget(new CustomLineEdit("Capabilities Pointer", width, height, "0x00000000", this));
    layout->addLayout(row14);

    QHBoxLayout* row15 = new QHBoxLayout();
    row15->addWidget(new QLabel("038h"));
    row15->addWidget(new CustomLineEdit("Expansion ROM Base Address", 4*width, height, "0x00000000", this));
    layout->addLayout(row15);

    QHBoxLayout* row16 = new QHBoxLayout();
    row16->addWidget(new QLabel("03Ch"));
    row16->addWidget(new CustomLineEdit("Bridge Control", 2*width, height, "0x00000000", this));
    row16->addWidget(new CustomLineEdit("Interrupt Pin", width, height, "0x00000000", this));
    row16->addWidget(new CustomLineEdit("Interrupt Line", width, height, "0x00000000", this));
    layout->addLayout(row16);

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