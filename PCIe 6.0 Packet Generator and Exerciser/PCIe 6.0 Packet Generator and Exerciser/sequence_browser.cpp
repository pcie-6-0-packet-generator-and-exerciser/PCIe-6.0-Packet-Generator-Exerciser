#include "sequence_browser.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QScrollBar>

using namespace Ui;

SequenceBrowser::SequenceBrowser(QWidget* parent)
	: QFrame(parent),
	sideBar_(nullptr)
{
	setMinimumSize(400, 400);
	createSideBar();
	createCardsSequence();
	manageLayout();
}

SequenceBrowser::~SequenceBrowser() 
{

}
void SequenceBrowser::createCardsSequence() {
	for (int i = 0; i < 10; ++i) {
		cards_.push_back(new TLPCard(this, "Card " + QString::number(i)));
	}
}
void SequenceBrowser::createSideBar() 
{
	sideBar_ = new QScrollBar(Qt::Vertical, this);
}

void SequenceBrowser::manageLayout() 
{
	QVBoxLayout* contentLayout = new QVBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(10);
	contentLayout->addWidget(sideBar_);

	setLayout(contentLayout);
}