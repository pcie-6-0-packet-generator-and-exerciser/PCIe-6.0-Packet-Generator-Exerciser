#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PCIe6PacketGeneratorandExerciser.h"

class PCIe6PacketGeneratorandExerciser : public QMainWindow
{
    Q_OBJECT

public:
    PCIe6PacketGeneratorandExerciser(QWidget *parent = nullptr);
    ~PCIe6PacketGeneratorandExerciser();

private:
    Ui::PCIe6PacketGeneratorandExerciserClass ui;
};
