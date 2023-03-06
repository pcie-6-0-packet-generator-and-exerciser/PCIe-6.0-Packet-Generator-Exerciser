#include "tlp_card.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>

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
	//tlp = new TLP();
	//tlp->header = new TLPHeader();
	setProperty(tlpCardProperty, true);
	setMinimumSize(200, 50);
	manageLayout();
}

TLPCard::~TLPCard()
{
	//delete tlp;
	delete textLabel_;
}

void TLPCard::manageLayout() {
	QVBoxLayout* contentLayout = new QVBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	contentLayout->addWidget(textLabel_, Qt::AlignCenter);
	setLayout(contentLayout);
}