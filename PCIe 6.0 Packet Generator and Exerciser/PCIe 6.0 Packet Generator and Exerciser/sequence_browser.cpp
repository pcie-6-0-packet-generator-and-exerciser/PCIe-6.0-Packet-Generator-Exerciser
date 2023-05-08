#include "sequence_browser.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

namespace {
	constexpr char transparentBackgroundProperty[] = "transparentBackground";
}
using namespace Ui;
SequenceBrowser::SequenceBrowser(QWidget* parent)
	: QFrame(parent)
{	
	setAcceptDrops(true);
	cardLayout_ = new QVBoxLayout;
	setProperty(::transparentBackgroundProperty, true);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);	
	createCardsSequence();
	manageLayout();
}

SequenceBrowser::~SequenceBrowser() 
{

}

void SequenceBrowser::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasFormat("application/x-tlp"))
		event->acceptProposedAction();
}

void SequenceBrowser::dropEvent(QDropEvent* event)
{
	QByteArray data = event->mimeData()->data("application/x-tlp");
	QDataStream stream(&data, QIODevice::ReadOnly);
	int value;
	stream >> value;
	TLPType tlpType = static_cast<TLPType>(value);
	TLPCard* card = new TLPCard(tlpType, this);

	cards_.push_back(card);
	card->setParent(this);
	cardLayout_->addWidget(card, 0, Qt::AlignHCenter | Qt::AlignTop);
		
	event->acceptProposedAction();
	
}

void SequenceBrowser::createCardsSequence() {
	//place holder
	/*TLPCard* card = new TLPCard(this, "Card ");
	cards_.push_back(card);*/
	
}


void SequenceBrowser::manageLayout() 
{
	/*QHBoxLayout* contentLayout = new QHBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	contentLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);*/

	cardLayout_->setContentsMargins(5, 5, 5, 5);
	cardLayout_->setSpacing(10);
	cardLayout_->setSizeConstraint(QLayout::SetMinimumSize);
	std::list<TLPCard>::iterator it;
	//contentLayout->addLayout(cardLayout_);
	setLayout(cardLayout_);

	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(30);
	effect->setOffset(0, 0);
	effect->setColor(Qt::black);

	setGraphicsEffect(effect);
}

std::queue<TLP*> SequenceBrowser::getTLPCards() {
	std::queue<TLP*> tlpCards;
	for (auto card : cards_) {
		tlpCards.push(card->tlp);
	}
	return tlpCards;
}