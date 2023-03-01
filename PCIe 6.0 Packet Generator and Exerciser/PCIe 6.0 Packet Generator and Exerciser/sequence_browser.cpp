#include "sequence_browser.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>


using namespace Ui;
SequenceBrowser::SequenceBrowser(QWidget* parent)
	: QFrame(parent),
	sideBar_(nullptr)
{
	setMinimumSize(400, 400);
	//createSideBar();
	//createCardsSequence();
	manageLayout();
}

SequenceBrowser::~SequenceBrowser() 
{

}
void SequenceBrowser::createCardsSequence() {
	

	for (int i = 0; i < 10; ++i) {
		cards_.push_back(new TLPCard(this, "Card " + QString::number(i)));

		
	}
	
}
void SequenceBrowser::createSideBar() 
{
	sideBar_ = new QScrollBar(Qt::Vertical, this);
}

void SequenceBrowser::manageLayout() 
{
	QHBoxLayout* contentLayout = new QHBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	sideBar_ = new QScrollBar(Qt::Vertical, this);
	contentLayout->addWidget(sideBar_);
	//contentLayout->addWidget(new TLPCard(this, "Card "));
	QVBoxLayout* cardLayout = new QVBoxLayout;
	cardLayout->setContentsMargins(0, 0, 0, 0);
	cardLayout->setSpacing(0);
	//contentLayout->addWidget(textLabel_, Qt::AlignCenter);
	for (int i = 0; i < 15; ++i) {
		cardLayout->addWidget(new TLPCard(this, "Card " + QString::number(i)));

	}
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(this);
	scrollArea->setVerticalScrollBar(sideBar_);
	//setLayout(cardLayout);
	contentLayout->addLayout(cardLayout);
	setLayout(contentLayout);
}