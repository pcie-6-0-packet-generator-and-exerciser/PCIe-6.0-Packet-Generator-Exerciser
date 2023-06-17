#include "sequence_browser.h"
#include "packet_details_widget.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMenu>
#include <QAction>

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

	setContextMenuPolicy(Qt::CustomContextMenu);
}

SequenceBrowser::~SequenceBrowser() 
{

}

void SequenceBrowser::setCurrentTab(currentTab tab) {
	currentTab_ = tab;
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
	//connect(card, &TLPCard::cardPressed, this->packetDetails, &PacketDetails::updateDetails);	
	connect(card, &TLPCard::cardPressed, this->packetDetails, [this, card] { this->packetDetails->updateView(card->tlp); });

	event->acceptProposedAction();

}
void SequenceBrowser::createCardsSequence() {
	//place holder
	/*TLPCard* card = new TLPCard(this, "Card ");
	cards_.push_back(card);*/
	
}
//void SequenceBrowser::generateTLPContextMenu(TLPCard* cardToDelete) {
//	QMenu menu;
//	QAction* deleteAction = new QAction(QString("Delete"), this);
//	QObject::connect(deleteAction, &QAction::triggered, [this, cardToDelete]() {
//		// Remove the card from the cards list and the layout, and destroy it
//		const auto cardIt = std::find(cards_.begin(), cards_.end(), cardToDelete);
//		if (cardIt != cards_.end()) {
//			auto* removedCard = *cardIt;
//			cardLayout_->removeWidget(removedCard);
//			cards_.erase(cardIt);
//			delete removedCard;
//		}
//	});
//	menu.addAction(deleteAction);
//	menu.popup(QCursor::pos());
}
//void SequenceBrowser::contextMenuEvent(QContextMenuEvent * event) {
//	TLPCard* cardToDelete = nullptr; for (auto* card : cards_) { if (card->geometry().contains(event->pos())) { cardToDelete = card; break; } }
//	if (cardToDelete != nullptr) {
//		generateTLPContextMenu(cardToDelete);
//	}
//	else {
//		QFrame::contextMenuEvent(event);
//	}
//}
void SequenceBrowser::contextMenuEvent(QContextMenuEvent* event)
{
	if (event->reason() == QContextMenuEvent::Reason::Mouse) {
		TLPCard* cardToDelete = nullptr;
		for (auto* card : cards_) {
			if (card->geometry().contains(event->pos())) {
				cardToDelete = card;
				break;
			}
		}

		if (cardToDelete != nullptr) {
			generateTLPContextMenu(cardToDelete);
		}
		else {
			QFrame::contextMenuEvent(event);
		}
	}
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
	int tag = 1;
	for (auto card : cards_) {
		card->tlp->header->nonBase->setTag(tag++);
		tlpCards.push(card->tlp);
	}
	return tlpCards;
}