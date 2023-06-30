#include "main_window.h"
#include "content_widget.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QFileDialog>
#include "enumeration_dialog.h"
#include "boost/dynamic_bitset.hpp"
#include "utils/tlp.h"



using namespace Ui;

MainWindow::MainWindow(QueueWrapper<TLP*>* rootComplexToLayers, QueueWrapper<TLP*>* layersToRootComplex)
    : QMainWindow(nullptr),
    rootComplexToLayers_(rootComplexToLayers),
    layersToRootComplex_(layersToRootComplex)
{
    setMinimumSize(1200, 800);
    setWindowTitle("PCIe6 Packet Generator and Exerciser");
    createContentWidget();
    //createToolBar(); //commented till implemented
    createMenuBar();
    manageLayout();
    //setWindowState(Qt::WindowMaximized);
    show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createToolBar() {
    toolBar_ = new QToolBar(this);

}
void MainWindow::createMenuBar() {
	QMenuBar* menuBar = new QMenuBar(this);
	QMenu* menu = new QMenu("File", menuBar);
	QAction* importAction = new QAction("Import Sequence", menu);
	menu->addAction(importAction);
	connect(importAction, &QAction::triggered, this, &MainWindow::importSequence);

    QAction* exportAction = new QAction("Export Sequence", menu);
    menu->addAction(exportAction);
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportSequence);

    menuBar->addMenu(menu);
    setMenuBar(menuBar);

}
boost::dynamic_bitset<> fromString(const QString& str) {
	boost::dynamic_bitset<> bitset(str.size());
    int size = str.size();
    for (int i = 0; i < size; i++) {
        if (str[i] == '1') {
			bitset.set((size -1) - i);
		}
	}
	return bitset;
}
void MainWindow::importSequence() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Sequence Files (*.csv)"));
    if (fileName.isEmpty()) {
		return;
	}
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QStringList seqList;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        seqList.append(line.split(',').first());
    }
    file.close();
    for (auto& seq : seqList) {
		boost::dynamic_bitset<> bitset = fromString(seq);
		TLP* tlp = TLP::getObjRep(bitset);
        contentWidget_->addTLPtoSequence(tlp);

	} 

}
void MainWindow::exportSequence() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Sequence Files (*.csv)"));
    if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
		return;
	}
    QTextStream stream(&file);
    std::queue<TLP*> sequence = contentWidget_->getSequence();
    string str;
    while (sequence.size() > 0) {
		TLP* tlp = sequence.front();
		sequence.pop();
        boost::to_string(tlp->getBitRep(),str );
		stream << QString::fromStdString(str) << ",\n";
	}

	file.close();
}
void MainWindow::createContentWidget() {
    contentWidget_ = new ContentWidget(this, rootComplexToLayers_, layersToRootComplex_);
}

void MainWindow::manageLayout(){
    setCentralWidget(contentWidget_);
}