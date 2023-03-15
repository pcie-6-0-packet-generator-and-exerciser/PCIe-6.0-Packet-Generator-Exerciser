#include "tlp_card.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <iostream>


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
	setMinimumSize(200, 100);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	manageLayout();
}

TLPCard::~TLPCard()
{
	//delete tlp;
	delete textLabel_;
}

void TLPCard::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		emit cardPressed(this);
	}
}


void TLPCard::mouseMoveEvent(QMouseEvent* event) {


	QDrag* drag = new QDrag(this);
	QMimeData* mimeData = new QMimeData;
	QByteArray data;
	QDataStream stream(&data, QIODevice::WriteOnly);
	//stream << static_cast<quintptr>(this);
	//stream << this;
	stream << textLabel_->text();
	mimeData->setData("application/x-tlp", data);
	drag->setMimeData(mimeData);
	drag->exec(Qt::CopyAction);
}



void TLPCard::manageLayout() {
	QVBoxLayout* contentLayout = new QVBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	contentLayout->addWidget(textLabel_, 0, Qt::AlignCenter | Qt::AlignHCenter);
	setLayout(contentLayout);
}