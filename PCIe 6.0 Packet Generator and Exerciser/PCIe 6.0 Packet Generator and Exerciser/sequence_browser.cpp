#include "sequence_browser.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>


using namespace Ui;
SequenceBrowser::SequenceBrowser(QWidget* parent)
	: QFrame(parent)
{	
	setAcceptDrops(true);
	cardLayout_ = new QVBoxLayout;
	setMinimumSize(500, 700);
	//setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	
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
	
	//place holder
	TLPCard* card = new TLPCard(this, "mem read 32b");
	
	card->setFixedSize(100, 100);
	cards_.push_back(card);
	card->setParent(this);
	cardLayout_->addWidget(card);
		
		event->acceptProposedAction();
	//}
}

void SequenceBrowser::createCardsSequence() {
	//place holder
	TLPCard* card = new TLPCard(this, "Card ");
	card->setFixedSize(50, 100);
	cards_.push_back(card);
	
}


void SequenceBrowser::manageLayout() 
{
	QHBoxLayout* contentLayout = new QHBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	contentLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

	cardLayout_->setContentsMargins(5, 5, 5, 5);
	cardLayout_->setSpacing(10);
	
	std::list<TLPCard>::iterator it;
	for (auto card : cards_) {
		cardLayout_->addWidget(card);
	}
	contentLayout->addLayout(cardLayout_);
	setLayout(contentLayout);

	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(30);
	effect->setOffset(0, 0);
	effect->setColor(Qt::black);

	setGraphicsEffect(effect);
}