//implement the result browser in result_browser.h
#include "result_browser.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>

namespace {
	constexpr char transparentBackgroundProperty[] = "transparentBackground";
}
using namespace Ui;
ResultBrowser::ResultBrowser(QWidget* parent)
	: QFrame(parent)
{
	cardLayout_ = new QVBoxLayout;
	setProperty(::transparentBackgroundProperty, true);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	manageLayout();
}

ResultBrowser::~ResultBrowser()
{
}

void ResultBrowser::createCardsSequence(std::queue<TLP*> incomingPackets) {
	//instantiate the cards and set the tlp to the tlp in the queue then add the card to cards_
	int expectedTag = 1;
	while(!incomingPackets.empty()) {
		TLP* incomingTlp = incomingPackets.front();
		incomingPackets.pop();
		int currentTag = incomingTlp->header->nonBase->getTag();
		
		//add empty cards in case of no completion. The -1 is for MessageNonHeaderBase getTag method in non_header_base.h
		while (currentTag < expectedTag || currentTag == -1) {
			TLPCard* emptyCard = new TLPCard();
			emptyCard->setStyleSheet("background: transparent;");
			cards_.push_back(emptyCard);
		}
		TLPCard* card = new TLPCard(incomingTlp, this);
		cards_.push_back(card);
	}
}

void ResultBrowser::manageLayout() {
	setLayout(cardLayout_);
}


