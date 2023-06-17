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

QString TLPenumToString(TLPType value)
{
	switch (value) {
	case TLPType::MemRead32:
		return "Memory Read 32b";
	case TLPType::MemRead64:
		return "Memory Read 64b";
	case TLPType::MemWrite32:
		return "Memory Write 32b";
	case TLPType::MemWrite64:
		return "Memory Write 64b";
	case TLPType::VendorMsg:
		return "Vendor Message";
	case TLPType::ConfigRead0:
		return "Configuration Read 0";
	case TLPType::ConfigWrite0:
		return "Configuration Write 0";
	case TLPType::ConfigRead1:
		return "Configuration Read 1";
	case TLPType::ConfigWrite1:
		return "Configuration Write 1";
	case TLPType::Cpl:
		return "Completion Without Data";
	case TLPType::CplD:
		return "Completion With Data";

	}
};

TLPCard::TLPCard(QWidget* parent) {
	//this function is called when a new tlp card is created
	//it sets the tlp type and creates a new tlp object based on the tlp type
	textLabel_ = new QLabel("", this);
	textLabel_->setAlignment(Qt::AlignHCenter);
	setProperty(tlpCardProperty, true);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	manageLayout();
}

TLPCard::TLPCard( TLPType tlpType, QWidget* parent)
	: QFrame(parent), textLabel_(new QLabel(TLPenumToString(tlpType), this))
{
	//this function is called when a new tlp card is created
	//it sets the tlp type and creates a new tlp object based on the tlp type

	boost::dynamic_bitset<> zeroPayload(32);
	

	this->tlpType = tlpType;
	switch (tlpType) {
	case TLPType::MemRead32:
		tlp = TLP::createMemRead32Tlp(0,  0, 0, 0, 0, 0);
		break;
	case TLPType::MemRead64:
		tlp = TLP::createMemRead64Tlp(0,  0, 0, 0, 0, 0);
		break;
	case TLPType::MemWrite32:
		tlp = TLP::createMemWrite32Tlp(1, zeroPayload, 0, 0, 0, 0, 0);
		break;
	case TLPType::MemWrite64:
		tlp = TLP::createMemWrite64Tlp(1, zeroPayload, 0, 0, 0, 0, 0);
		break;
	case TLPType::VendorMsg:
		tlp = TLP::createVendorMsgTlp(1, zeroPayload, 0, 0, 0);
		break;
	case TLPType::ConfigRead0:
		tlp = TLP::createConfigRead0Tlp(0, 0, 0, 0, 0, 0, 0, 0, 0);
		break;
	case TLPType::ConfigWrite0:
		tlp = TLP::createConfigWrite0Tlp(1, zeroPayload, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
		break;
	case TLPType::ConfigRead1:
		tlp = TLP::createConfigRead1Tlp(0, 0, 0, 0, 0, 0, 0, 0, 0);
		break;
	case TLPType::ConfigWrite1:
		tlp = TLP::createConfigWrite1Tlp(1, zeroPayload, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		break;
	}
	textLabel_->setAlignment(Qt::AlignHCenter);
	setProperty(tlpCardProperty, true);
	setMinimumSize(200, 100);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	manageLayout();
}

TLPCard::TLPCard(TLP* tlp, QWidget* parent) {
	textLabel_ = new QLabel(TLPenumToString(tlp->header->TLPtype), this);
	this->tlp = tlp;
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

void TLPCard::setCurrentTab(currentTab tab) {
	currentTab_ = tab;
}





void TLPCard::mouseMoveEvent(QMouseEvent* event) {
	//if the currentTab is resultExplorer, return
	if (currentTab_ == currentTab::resultExplorer) {
		return;
	}
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
