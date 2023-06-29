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
#include "utils/tlp.h"
#include "tlp_card.h"
#include <QRandomGenerator>

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
void SequenceBrowser::setEditable(bool editable) {
	editable_ = editable;
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


void SequenceBrowser::deleteTLP(TLPCard* card) {
	//delete card from tlp cards and remove its widget from the layout
	cards_.remove(card);
	//cardLayout_->removeWidget(card);
	if (card != nullptr) {
		card->hide();
		cardLayout_->removeWidget(card);
		card->deleteLater();
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
	int tag = 0;
	for (auto card : cards_) {
		card->tlp->header->nonBase->setTag(tag++);
		tlpCards.push(card->tlp);
	}
	return tlpCards;
}

void SequenceBrowser::onGenerateSequenceClick() {
	//Open a generate sequence dialog
	dialog_ = new GenerateSequenceDialog;
	dialog_->setModal(true);
	dialog_->show();
	connect(dialog_, &GenerateSequenceDialog::accepted, this, &SequenceBrowser::onGenerateSequenceDialogAccepted);
	connect(dialog_->submitButton_, &QPushButton::clicked, this, &SequenceBrowser::onGenerateSequenceDialogAccepted);
}

void SequenceBrowser::onGenerateSequenceDialogAccepted() {
	std::bitset<4> BE(15);
	boost::dynamic_bitset<> zeroPayload(32);

	//Generate a sequence of TLPs based on the dialog input
	if (dialog_->getTlpType() == 0) {
		int address = 0;
		for (int i = 0; i < dialog_->getSequenceLength(); i++) {
			TLP* tlp = TLP::createMemRead32Tlp(1, 0, 0, address++, BE, BE);
			TLPCard* card = new TLPCard(tlp, this);
			connect(card, &TLPCard::cardPressed, this->packetDetails, [this, card] { this->packetDetails->updateView(card->tlp); });

			cardLayout_->addWidget(card, 0, Qt::AlignHCenter | Qt::AlignTop);

		}
	}
	else if (dialog_->getTlpType() == 1) {
		int address = 0;
		for (int i = 0; i < dialog_->getSequenceLength(); i++) {
			TLP* tlp = TLP::createMemRead64Tlp(1, 0, 0, address++, BE, BE);
			TLPCard* card = new TLPCard(tlp, this);
			connect(card, &TLPCard::cardPressed, this->packetDetails, [this, card] { this->packetDetails->updateView(card->tlp); });

			cardLayout_->addWidget(card, 0, Qt::AlignHCenter | Qt::AlignTop);

		}
	}
	else if (dialog_->getTlpType() == 2) {
		QRandomGenerator* generator = QRandomGenerator::global();
		int address = 0;
		int data = dialog_->getInitialValue();
		for (int i = 0; i < dialog_->getSequenceLength(); i++) {
			boost::dynamic_bitset<> payload(32 ,data);
			TLP* tlp = TLP::createMemWrite32Tlp(1, payload, 0, 0, address++, BE, BE);
			TLPCard* card = new TLPCard(tlp, this);
			connect(card, &TLPCard::cardPressed, this->packetDetails, [this, card] { this->packetDetails->updateView(card->tlp); });
			cardLayout_->addWidget(card, 0, Qt::AlignHCenter | Qt::AlignTop);


			if (dialog_->getSequenceType() == 0) {
				data+= dialog_->getStepSize();
			}
			else if (dialog_->getSequenceType() == 1) {
				data -= dialog_->getStepSize();
			}
			else {
				data = generator->bounded(0, 100000);
			}
		}
	}
	else {
		QRandomGenerator* generator = QRandomGenerator::global();
		int address = 0;
		int data = dialog_->getInitialValue();
		for (int i = 0; i < dialog_->getSequenceLength(); i++) {
			boost::dynamic_bitset<> payload(32, data);
			TLP* tlp = TLP::createMemWrite64Tlp(1, payload, 0, 0, address++, BE, BE);
			TLPCard* card = new TLPCard(tlp, this);
			connect(card, &TLPCard::cardPressed, this->packetDetails, [this, card] { this->packetDetails->updateView(card->tlp); });

			if (dialog_->getSequenceType() == 0) {
				data += dialog_->getStepSize();
			}
			else if (dialog_->getSequenceType() == 1) {
				data -= dialog_->getStepSize();
			}
			else {
				data = generator->bounded(0, 100000);
			}
			cardLayout_->addWidget(card, 0, Qt::AlignHCenter | Qt::AlignTop);

		}
	}
	dialog_->close();
}