#include "tlp_card.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <iostream>
#include <bitset>
#include "utils/tlp.h"
#include <boost/dynamic_bitset.hpp>



namespace
{
	constexpr char tlpCardProperty[] = "tlpCard";
}
using namespace Ui;




TLPCard::TLPCard( TLPType tlpType, QWidget* parent)
	: QFrame(parent), textLabel_(new QLabel(TLPenumToString(tlpType), this))
{
	//this function is called when a new tlp card is created
	//it sets the tlp type and creates a new tlp object based on the tlp type

	boost::dynamic_bitset<> zeroPayload(0);
	

	this->tlpType = tlpType;
	switch (tlpType) {
	case TLPType::MemRead32:
		tlp = TLP::createMemRead32Tlp(0, 0, 0, 0, 0);
		break;
	case TLPType::MemRead64:
		tlp = TLP::createMemRead64Tlp(0, 0, 0, 0, 0);
		break;
	case TLPType::MemWrite32:
		tlp = TLP::createMemWrite32Tlp(0, zeroPayload, 0, 0, 0, 0, 0);
		break;
	case TLPType::MemWrite64:
		tlp = TLP::createMemWrite64Tlp(0, zeroPayload, 0, 0, 0, 0, 0);
		break;
	case TLPType::VendorMsg:
		tlp = TLP::createVendorMsgTlp(0, zeroPayload, 0, 0, 0);
		break;
	case TLPType::ConfigRead0:
		tlp = TLP::createConfigRead0Tlp(0, 0, 0, 0, 0, 0, 0, 0, 0);
		break;
	case TLPType::ConfigWrite0:
		tlp = TLP::createConfigWrite0Tlp(0, zeroPayload, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
		break;
	case TLPType::ConfigRead1:
		tlp = TLP::createConfigRead1Tlp(0, 0, 0, 0, 0, 0, 0, 0, 0);
		break;
	case TLPType::ConfigWrite1:
		tlp = TLP::createConfigWrite1Tlp(0, zeroPayload, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		break;
	}
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


void TLPCard::mouseMoveEvent(QMouseEvent* event) {


	QDrag* drag = new QDrag(this);
	QMimeData* mimeData = new QMimeData;
	QByteArray data;
	QDataStream stream(&data, QIODevice::WriteOnly);
	stream << static_cast<int>(tlpType);
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
