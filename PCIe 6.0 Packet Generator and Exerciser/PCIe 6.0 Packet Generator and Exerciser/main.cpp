#include "main_window.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include "utils/queue_wrapper.h"
#include "utils/tlp.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile styleFile(":/PCIe6PacketGeneratorandExerciser/style.qss");
    styleFile.open(QFile::ReadOnly);

    if(styleFile.isOpen() == false)
		return -1;
    QString style(styleFile.readAll());
    app.setStyleSheet(style);
    QueueWrapper<TLP*>* rootComplexToLayers = new QueueWrapper<TLP*>();
    QueueWrapper<TLP*>* layersToRootComplex = new QueueWrapper<TLP*>();
    Ui::MainWindow* mainWindow = new Ui::MainWindow(rootComplexToLayers, layersToRootComplex);
    mainWindow->show();
    return app.exec();
}
