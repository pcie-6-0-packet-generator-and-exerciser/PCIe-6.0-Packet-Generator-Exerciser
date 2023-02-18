#include "PCIe6PacketGeneratorandExerciser.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PCIe6PacketGeneratorandExerciser w;
    w.show();
    return a.exec();
}
