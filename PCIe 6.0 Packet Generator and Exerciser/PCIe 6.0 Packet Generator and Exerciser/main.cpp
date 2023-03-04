#include "main_window.h"
#include <QtWidgets/QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile styleFile(":/PCIe6PacketGeneratorandExerciser/style.qss");
    styleFile.open(QFile::ReadOnly);

    if(styleFile.isOpen() == false)
		return -1;
    QString style(styleFile.readAll());
    app.setStyleSheet(style);

    Ui::MainWindow* mainWindow = new Ui::MainWindow();
    mainWindow->show();
    return app.exec();
}
