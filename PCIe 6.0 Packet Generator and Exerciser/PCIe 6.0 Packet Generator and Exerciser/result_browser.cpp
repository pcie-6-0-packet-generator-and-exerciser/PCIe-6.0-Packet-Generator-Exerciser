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
	while(!incomingPackets.empty()) {
		TLP* incomingTlp = incomingPackets.front();
		incomingPackets.pop();
		TLPCard* card = new TLPCard(incomingTlp, this);
		cards_.push_back(card);
	}
}

void ResultBrowser::manageLayout() {
	setLayout(cardLayout_);
}


