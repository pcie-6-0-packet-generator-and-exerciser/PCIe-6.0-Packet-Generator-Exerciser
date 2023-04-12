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
	clearView();
	
	QLabel* label = new QLabel(QString("TLPCard details"), this);
	contentLayout_->addWidget(label);
}

void PacketDetails::clearView() {
	// Removes any existing content from the view
	QLayoutItem* child;
	while ((child = contentLayout_->takeAt(0)) != nullptr) {
		delete child->widget();
		delete child;
	}
}

void PacketDetails:: manageLayout() {
	contentLayout_->setContentsMargins(0, 0, 0, 0);
	contentLayout_->setSpacing(10);

	
	setLayout(contentLayout_);

	
}