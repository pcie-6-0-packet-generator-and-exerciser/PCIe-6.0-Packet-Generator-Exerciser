#include "sequence_browser.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>


using namespace Ui;
SequenceBrowser::SequenceBrowser(QWidget* parent)
	: QFrame(parent)
{	
	setMaximumWidth(300);
	//createCardsSequence();
	manageLayout();
}

SequenceBrowser::~SequenceBrowser() 
{

}
//void SequenceBrowser::createCardsSequence() {
//	
//
//	for (int i = 0; i < 40; ++i) {
//		TLPCard* card = new TLPCard(this, "Card " + QString::number(i));
//		card->setFixedSize(50, 100);
//		cards_.push_back(card);
//
//		
//	}
//	
//}


void SequenceBrowser::manageLayout() 
{
	QHBoxLayout* contentLayout = new QHBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	QScrollBar* sideBar = new QScrollBar(Qt::Vertical, this);
	contentLayout->addWidget(sideBar);
	//contentLayout->addWidget(new TLPCard(this, "Card "));
	QVBoxLayout* cardLayout = new QVBoxLayout;
	cardLayout->setContentsMargins(0, 0, 0, 0);
	cardLayout->setSpacing(0);
	//contentLayout->addWidget(textLabel_, Qt::AlignCenter);
	std::list<TLPCard>::iterator it;
	for (auto card : cards_) {
		cardLayout->addWidget(card);
	}
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setFixedSize(200, 400);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(this);
	scrollArea->setVerticalScrollBar(sideBar);
	//setLayout(cardLayout);
	contentLayout->addLayout(cardLayout);
	setLayout(contentLayout);
}