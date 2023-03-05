#include "sequence_browser.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>

using namespace Ui;
SequenceBrowser::SequenceBrowser(QWidget* parent)
	: QFrame(parent)
{	
	setFixedWidth(500);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	createCardsSequence();
	manageLayout();
}

SequenceBrowser::~SequenceBrowser() 
{

}
void SequenceBrowser::createCardsSequence() {
	

	for (int i = 0; i < 40; ++i) {
		TLPCard* card = new TLPCard(this, "Card " + QString::number(i));
		card->setFixedSize(50, 100);
		cards_.push_back(card);
		
	}
	
}


void SequenceBrowser::manageLayout() 
{
	QHBoxLayout* contentLayout = new QHBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	//QScrollBar* sideBar = new QScrollBar(Qt::Vertical, this);
	//contentLayout->addWidget(sideBar);
	//contentLayout->addWidget(new TLPCard(this, "Card "));
	QVBoxLayout* cardLayout = new QVBoxLayout;
	cardLayout->setContentsMargins(0, 0, 0, 0);
	cardLayout->setSpacing(10);
	//contentLayout->addWidget(textLabel_, Qt::AlignCenter);
	std::list<TLPCard>::iterator it;
	for (auto card : cards_) {
		cardLayout->addWidget(card);
	}
	/*QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setFixedSize(200, 400);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(this);*/

	/*scrollarea->setverticalscrollbar(sidebar);*/
	//setLayout(cardLayout);
	contentLayout->addLayout(cardLayout);
	setLayout(contentLayout);

	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(30);
	effect->setOffset(0, 0);
	effect->setColor(Qt::black);

	setGraphicsEffect(effect);
}