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
	setProperty(tlpCardProperty, true);
	setMinimumSize(300 , 50);
	setMaximumSize(parent->width() - 100, 300);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	manageLayout();
}

TLPCard::~TLPCard()
{
	delete textLabel_;
}

void TLPCard::manageLayout() {
	QVBoxLayout* contentLayout = new QVBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	contentLayout->addWidget(textLabel_, Qt::AlignCenter);
	setLayout(contentLayout);
}