#include "packet_details_widget.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>


using namespace Ui;

PacketDetails::PacketDetails(QWidget* parent)
	: QFrame(parent)

{
	contentLayout_ = new QVBoxLayout;
	manageLayout();
}
PacketDetails::~PacketDetails()
{
}

void PacketDetails::updateDetails() {
	//place holder
	QLabel* label = new QLabel(QString("TLPCard details"), this);
	contentLayout_->addWidget(label);
}


void PacketDetails:: manageLayout() {
	contentLayout_->setContentsMargins(0, 0, 0, 0);
	contentLayout_->setSpacing(10);

	
	setLayout(contentLayout_);

	
}