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
	createCardsSequence();
	manageLayout();
}

ResultBrowser::~ResultBrowser()
{
}

void ResultBrowser::createCardsSequence() {
	//place holder
	/*TLPCard* card = new TLPCard(this, "Card ");
		cards_.push_back(card);*/
}

void ResultBrowser::manageLayout() {
	setLayout(cardLayout_);
}


