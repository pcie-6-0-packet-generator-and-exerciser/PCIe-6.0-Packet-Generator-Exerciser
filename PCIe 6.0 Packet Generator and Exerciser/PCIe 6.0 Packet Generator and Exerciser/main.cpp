#include "main_window.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include "utils/queue_wrapper.h"
#include "utils/tlp.h"
#include "layers/flit.h"
#include "Endpoint/endpoint_app/endpoint_app.h"
#include "layers/globals.h"
#include "layers/thread_functions.h"
#include <thread>
#include <QRandomGenerator>
#include <QTime>
#include "enumeration_dialog.h"
#include <QThread>
#include <QTimer>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile styleFile(":/PCIe6PacketGeneratorandExerciser/style.qss");
    styleFile.open(QFile::ReadOnly);

    if(styleFile.isOpen() == false)
		return -1;
    QString style(styleFile.readAll());
    app.setStyleSheet(style);
    int credit[12][2];
    for (int i = 0; i < 12; i++) {
        credit[i][0] = 100;
        credit[i][1] = 2000;
    }
    
    QueueWrapper<TLP*> rootComplexToRootComplexLayers;
    QueueWrapper<TLP*> rootComplexLayersToRootComplex;
    QueueWrapper<Flit*> rootComplexLayersToEndpointLayers;
    QueueWrapper<Flit*> endpointLayersToRootComplexLayers;
    QueueWrapper<TLP*> endpointLayersToEndpoint;
    QueueWrapper<TLP*> endpointToEndpointLayers;
  
    Globals rootComplexGlobal(credit[0], credit[1], credit[2], credit[3], credit[4], credit[5]);
    Globals endpointGlobal(credit[6], credit[7], credit[8], credit[9], credit[10], credit[11]);

    std::thread t1(initilizationSender, std::ref(rootComplexGlobal), std::ref(rootComplexToRootComplexLayers), std::ref(rootComplexLayersToEndpointLayers));
    std::thread t2(initilizationSender, std::ref(endpointGlobal), std::ref(endpointToEndpointLayers), std::ref(endpointLayersToRootComplexLayers));

    std::thread t3(initializationReceiver, std::ref(rootComplexGlobal), std::ref(endpointLayersToRootComplexLayers), std::ref(rootComplexLayersToRootComplex));
    std::thread t4(initializationReceiver, std::ref(endpointGlobal), std::ref(rootComplexLayersToEndpointLayers), std::ref(endpointLayersToEndpoint));
    
    

    EndpointApp* endpointApp = new EndpointApp();
    std::thread t5(&EndpointApp::run, endpointApp, std::ref(endpointToEndpointLayers), std::ref(endpointLayersToEndpoint));

    Ui::MainWindow* mainWindow = new Ui::MainWindow(&rootComplexToRootComplexLayers, &rootComplexLayersToRootComplex);
    
    PcieEnumerationDialog* enumerationDialog = new PcieEnumerationDialog(nullptr);
    enumerationDialog->setModal(true);
    enumerationDialog->show();
    QApplication::processEvents();
    QThread::sleep(1.5);
    while (!endpointGlobal.Fl2 || !rootComplexGlobal.Fl2) {
        QThread::sleep(1);
    }
    QTime* time = new QTime();
    QRandomGenerator* randomGenerator = new QRandomGenerator(time->msecsSinceStartOfDay());
    enumerationDialog->setMessage("Enumeration of the PCIe is currently running...<br><br>One Endpoint Detected<br><br>Fetching Memory Ranges<br><br>Memory Ranges Fetched<br><br>Prefetchable memory assigned address range 0 -> 33554431<br><br>non-prefetchable assigned address range 33554432 -> 35651583<br><br>Link initialization in progress...<br><br>Initialization is Done<br>");
    QApplication::processEvents();
    app.exec();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    return 0;
}