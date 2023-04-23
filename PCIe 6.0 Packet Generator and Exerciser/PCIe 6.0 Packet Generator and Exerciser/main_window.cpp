#include "main_window.h"
#include "content_widget.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QPushButton>
using namespace Ui;

MainWindow::MainWindow(QueueWrapper<TLP*>* rootComplexToLayers, QueueWrapper<TLP*>* layersToRootComplex)
    : QMainWindow(nullptr),
    rootComplexToLayers_(rootComplexToLayers),
    layersToRootComplex_(layersToRootComplex)
{
    setMinimumSize(1200, 800);
    setWindowTitle("PCIe6 Packet Generator and Exerciser");
    createContentWidget();
    createToolBar();
    manageLayout();
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