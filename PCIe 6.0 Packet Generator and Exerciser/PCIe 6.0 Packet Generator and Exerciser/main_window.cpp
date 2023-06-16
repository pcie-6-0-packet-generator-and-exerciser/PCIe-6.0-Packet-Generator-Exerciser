#include "main_window.h"
#include "content_widget.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QPushButton>
#include "enumeration_dialog.h"

using namespace Ui;

MainWindow::MainWindow(QueueWrapper<TLP*>* rootComplexToLayers, QueueWrapper<TLP*>* layersToRootComplex)
    : QMainWindow(nullptr),
    rootComplexToLayers_(rootComplexToLayers),
    layersToRootComplex_(layersToRootComplex)
{
    src::severity_logger_mt<boost::log::trivial::severity_level>& my_logger = my_logger::get();
    BOOST_LOG_SEV(my_logger, logging::trivial::trace) << "MainWindow::MainWindow()";
    setMinimumSize(1200, 800);
    setWindowTitle("PCIe6 Packet Generator and Exerciser");
    createContentWidget();
    createToolBar();
    manageLayout();
    show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createToolBar() {
    toolBar_ = new QToolBar(this);

}

void MainWindow::createContentWidget() {
    contentWidget_ = new ContentWidget(this, rootComplexToLayers_, layersToRootComplex_);
}

void MainWindow::manageLayout(){
    setCentralWidget(contentWidget_);
}