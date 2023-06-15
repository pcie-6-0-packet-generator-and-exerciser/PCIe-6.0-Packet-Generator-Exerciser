#include "type_browser.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QDrag>
#include<QMimeData>
#include <QMouseEvent>

namespace {
	constexpr char transparentBackgroundProperty[] = "transparentBackground";
}

using namespace Ui;
TypeBrowser::TypeBrowser(QWidget* parent)
	: QFrame(parent)
{
	setAcceptDrops(true);
	setProperty(::transparentBackgroundProperty, true);
	//setMinimumSize(500, 700);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
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


	constexpr std::array<TLPType, 9> tlpTypes = { TLPType::MemRead32, TLPType::MemRead64,TLPType::MemWrite32,TLPType::MemWrite64,TLPType::VendorMsg,
											TLPType::ConfigRead0,TLPType::ConfigWrite0, TLPType::ConfigRead1,TLPType::ConfigWrite1 };
	for (TLPType value : tlpTypes) {
		TLPCard* card = new TLPCard(value, this);
		cards_.push_back(card);
	}
}


void TypeBrowser::manageLayout()
{
	QVBoxLayout* cardLayout = new QVBoxLayout;
	cardLayout->setContentsMargins(0, 0, 0, 0);
	cardLayout->setSpacing(10);

	std::list<TLPCard>::iterator it;
	for (auto card : cards_) {
		cardLayout->addWidget(card, 0 , Qt::AlignHCenter);
	}	
	setLayout(cardLayout);

	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(30);
	effect->setOffset(0, 0);
	effect->setColor(Qt::black);

	setGraphicsEffect(effect);
}

