#pragma once
#include <QtWidgets/QMainWindow>
#include "utils/queue_wrapper.h"

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
    public slots:
        void importSequence();
        void exportSequence();
    private:
        void createContentWidget();
        void createToolBar();
        void manageLayout();
        void createMenuBar();
    

    private:
        QToolBar* toolBar_;
        ContentWidget* contentWidget_;
        QueueWrapper<TLP*>* rootComplexToLayers_;
        QueueWrapper<TLP*>* layersToRootComplex_;

   
    };

}
