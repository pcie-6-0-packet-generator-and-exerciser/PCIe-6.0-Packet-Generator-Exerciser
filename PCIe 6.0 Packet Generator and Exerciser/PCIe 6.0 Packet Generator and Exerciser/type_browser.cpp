#include "type_browser.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QDrag>
#include<QMimeData>
#include <QMouseEvent>


using namespace Ui;
TypeBrowser::TypeBrowser(QWidget* parent)
	: QFrame(parent)
{
	setAcceptDrops(true);
	setFixedWidth(500);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	createCardsSequence();
	manageLayout();
}

TypeBrowser::~TypeBrowser()
{

}

void TypeBrowser::dragEnterEvent(QDragEnterEvent* event)
{
	event->acceptProposedAction();
}

//void TypeBrowser::dropEvent(QDropEvent* event)
//{
//	event->acceptProposedAction();
//
//}
// 







void TypeBrowser::createCardsSequence() {


	/*for (int i = 0; i < 40; ++i) {
		TLPCard* card = new TLPCard(this, "Card " + QString::number(i));
		card->setFixedSize(50, 100);
		cards_.push_back(card);

	}*/
	TLPCard* card = new TLPCard(this, "mem read 32b");
	//card->tlp = new TLP();
	/*card->tlp->header = new TLPHeader();
	card->tlp->header->nonBase = new AddressRouting32Bit(5,10);
	card->tlp->header->TLPtype = TLPType::MemRead32;*/
	card->setFixedSize(100, 100);
	cards_.push_back(card);
	TLPCard* card2 = new TLPCard(this, "mem read 64b");
	//card->tlp = new TLP();
	/*card->tlp->header = new TLPHeader();
	card->tlp->header->nonBase = new AddressRouting32Bit(5,10);
	card->tlp->header->TLPtype = TLPType::MemRead32;*/
	card->setFixedSize(100, 100);
	cards_.push_back(card2);

	
}


void TypeBrowser::manageLayout()
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

