#include "main_window.h"
#include "content_widget.h"

#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QPushButton>
using namespace Ui;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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
    contentWidget_ = new ContentWidget(this);
}

void MainWindow::manageLayout(){
    setCentralWidget(contentWidget_);
}