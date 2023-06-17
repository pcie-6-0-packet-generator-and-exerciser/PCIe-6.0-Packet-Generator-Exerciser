//implement the result browser in result_browser.h
#include "result_browser.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include "packet_details_widget.h"
namespace {
	constexpr char transparentBackgroundProperty[] = "transparentBackground";
}
using namespace Ui;
ResultBrowser::ResultBrowser(QWidget* parent, PacketDetails* packetDetails)
	: QFrame(parent)
{
	packetDetails_ = packetDetails;
	cardLayout_ = new QVBoxLayout;
	setProperty(::transparentBackgroundProperty, true);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	//manageLayout();
}

ResultBrowser::~ResultBrowser()
{
}

void ResultBrowser::createCardsSequence(std::queue<TLP*> incomingPackets) {
	for (auto card : cards_) {
		cardLayout_->removeWidget(card);
		delete card;
	}
	cards_.clear();
	//clear the layout and add the cards to the layout
	
	//instantiate the cards and set the tlp to the tlp in the queue then add the card to cards_
	int expectedTag = 0;
	while(!incomingPackets.empty()) {
		TLP* incomingTlp = incomingPackets.front();
		incomingPackets.pop();
		int currentTag = incomingTlp->header->nonBase->getTag();
		
		//add empty cards in case of no completion. The -1 is for MessageNonHeaderBase getTag method in non_header_base.h
		if (currentTag != expectedTag || currentTag == -1) {
			TLPCard* emptyCard = new TLPCard();
			emptyCard->setCurrentTab(currentTab::resultExplorer);
			emptyCard->setStyleSheet("background: transparent;");
			cards_.push_back(emptyCard);
		}
		expectedTag++;
		TLPCard* card = new TLPCard(incomingTlp, this);
		//connect(card, &TLPCard::cardPressed, this->packetDetails_, [this, card] { this->packetDetails_->updateView(card->tlp); });

		//card->setCurrentTab(currentTab::resultExplorer);
		cards_.push_back(card);
	}
	manageLayout();
}

void ResultBrowser::manageLayout() {
	
	for (auto card : cards_) {
		cardLayout_->addWidget(card, 0, Qt::AlignHCenter | Qt::AlignTop);
		connect(card, &TLPCard::cardPressed, this->packetDetails_, [this, card] { this->packetDetails_->updateView(card->tlp); });
	}
	setLayout(cardLayout_);
}


