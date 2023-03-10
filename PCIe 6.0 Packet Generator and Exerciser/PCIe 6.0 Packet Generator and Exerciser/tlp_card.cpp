#include "tlp_card.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>

namespace
{
	constexpr char tlpCardProperty[] = "tlpCard";
}
using namespace Ui;

TLPCard::TLPCard(QWidget* parent, QString text)
	: QFrame(parent),
	textLabel_(new QLabel(text, this))
{
	
	textLabel_->setAlignment(Qt::AlignHCenter);
	setProperty(tlpCardProperty, true);
	setMinimumSize(200, 50);
	manageLayout();
}

TLPCard::~TLPCard()
{
	//delete tlp;
	delete textLabel_;
}
void TLPCard::mouseMoveEvent(QMouseEvent* event) {
	if ((event->buttons() & Qt::LeftButton)) {
		QMimeData* mime = new QMimeData;
		mime->data("application/x-tlpcard");
		QDrag* drag = new QDrag(this);
		drag->setMimeData(mime);
		drag->setHotSpot(event->pos());
		drag->exec(Qt::MoveAction);
	}
}



void TLPCard::manageLayout() {
	QVBoxLayout* contentLayout = new QVBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	contentLayout->addWidget(textLabel_, Qt::AlignCenter);
	setLayout(contentLayout);
}