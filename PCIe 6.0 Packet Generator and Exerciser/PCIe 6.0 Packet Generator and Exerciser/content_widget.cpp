#include "content_widget.h"
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>

#include "sequence_browser.h"
#include "type_browser.h"

namespace {
	constexpr char headerFrameProperty[] = "headerFrame";
	constexpr char centralTitleProperty[] = "centralTitle";
}
using namespace Ui;

ContentWidget::ContentWidget(QWidget* parent)
	: QFrame(parent)
{
	createHeader();
	createBody();
	manageLayout();
}

ContentWidget::~ContentWidget()
{

}

void ContentWidget::createHeader() 
{
	header_ = new QFrame(this);
	header_->setProperty(::headerFrameProperty, true);
	QLabel* titleLabel = new QLabel("PCIe 6.0 Packet Generator and Exerciser", header_);
	titleLabel->setProperty(::centralTitleProperty, true);
	titleLabel->setAlignment(Qt::AlignCenter);
	QHBoxLayout* headerLayout = new QHBoxLayout;
	headerLayout->setContentsMargins(0, 0, 0, 0);
	headerLayout->setSpacing(0);
	headerLayout->addWidget(titleLabel);

	header_->setLayout(headerLayout);
}

void ContentWidget::createBody() 
{
	body_ = new QFrame(this);
	QHBoxLayout* bodyLayout = new QHBoxLayout;
	bodyLayout->setContentsMargins(20, 20, 20, 20);
	bodyLayout->setSpacing(3);	
	//for type browser
	TypeBrowser* typeBrowser = new TypeBrowser(body_);
	


	QScrollBar* typeSideBar = new QScrollBar(Qt::Vertical, nullptr);

	QScrollArea* typeScrollArea = new QScrollArea;
	typeScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//typeScrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	typeScrollArea->setBackgroundRole(QPalette::Dark);
	typeScrollArea->setWidgetResizable(true);
	typeScrollArea->setVerticalScrollBar(typeSideBar);
	typeScrollArea->setWidget(typeBrowser);
	bodyLayout->addWidget(typeScrollArea);
	bodyLayout->setStretchFactor(typeScrollArea, 1);
	SequenceBrowser* sequenceBrowser = new SequenceBrowser(body_);
	

	QScrollBar* sequenceSideBar = new QScrollBar(Qt::Vertical, nullptr);

	QScrollArea* sequenceScrollArea = new QScrollArea;
	/*QVBoxLayout* sequenceLayout = new QVBoxLayout;
	sequenceLayout->setContentsMargins(10, 10, 10, 10);
	sequenceLayout->addWidget(sequenceBrowser);
	*///sequenceScrollArea->setLayout(sequenceLayout);
	sequenceScrollArea->setWidget(sequenceBrowser);
	sequenceScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	sequenceScrollArea->setWidgetResizable(true);
	sequenceScrollArea->setVerticalScrollBar(sequenceSideBar);

	sequenceScrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	bodyLayout->addWidget(sequenceScrollArea);
	bodyLayout->setStretchFactor(sequenceScrollArea, 1);

	

	/*QWidget* spacer = new QWidget(body_);
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	bodyLayout->addWidget(spacer);*/
	body_->setLayout(bodyLayout);
}

void ContentWidget::manageLayout() 
{
	QVBoxLayout* contentLayout = new QVBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	contentLayout->addWidget(header_);
	contentLayout->setStretchFactor(header_, 1);
	contentLayout->addWidget(body_);
	contentLayout->setStretchFactor(body_, 8);

	setLayout(contentLayout);

	//setStyleSheet("border: red 2px solid;");
}