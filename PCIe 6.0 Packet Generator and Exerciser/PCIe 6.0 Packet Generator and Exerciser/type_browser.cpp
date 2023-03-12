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


	/*for (int i = 0; i < 40; ++i) {
		TLPCard* card = new TLPCard(this, "Card " + QString::number(i));
		card->setFixedSize(50, 100);
		cards_.push_back(card);

	}*/
	TLPCard* card = new TLPCard(this, "mem read 32b");
	cards_.push_back(card);

	TLPCard* card2 = new TLPCard(this, "mem read 64b");
	cards_.push_back(card2);
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

