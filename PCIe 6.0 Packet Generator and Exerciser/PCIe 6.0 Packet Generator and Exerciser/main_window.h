#pragma once
#include <QtWidgets/QMainWindow>
#include "utils/queue_wrapper.h"
#include "logging.h"

class QToolBar;
class TLP;
namespace Ui
{
    class ContentWidget;
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QueueWrapper<TLP*>* rootComplexToLayers, QueueWrapper<TLP*>* layersToRootComplex);
        ~MainWindow();
    private:
        void createContentWidget();
        void createToolBar();
        void manageLayout();

    private:
        QToolBar* toolBar_;
        ContentWidget* contentWidget_;
        QueueWrapper<TLP*>* rootComplexToLayers_;
        QueueWrapper<TLP*>* layersToRootComplex_;
    };

}
