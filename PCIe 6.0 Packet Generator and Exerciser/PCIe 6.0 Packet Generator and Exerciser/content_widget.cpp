#include "content_widget.h"
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>

#include "sequence_browser.h"
#include "type_browser.h"
#include "result_browser.h"
#include"packet_details_widget.h"

namespace {
	constexpr char headerFrameProperty[] = "headerFrame";
	constexpr char centralTitleProperty[] = "centralTitle";
	constexpr char widgetTitleProperty[] = "widgetTitle";
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

	
	//type browser
	QVBoxLayout* typeLayout = new QVBoxLayout;
	typeLayout->setContentsMargins(5, 5, 5, 5);
	typeLayout->setSpacing(10);

	QLabel* typeLabel = new QLabel("Types Browser", body_);
	typeLabel->setProperty(::widgetTitleProperty, true);
	typeLabel->setMinimumWidth(300);
	typeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	typeLayout->addWidget(typeLabel, 1, Qt::AlignHCenter);
	typeLayout->setStretchFactor(typeLabel, 1);

	TypeBrowser* typeBrowser = new TypeBrowser(body_);
	QScrollBar* typeSideBar = new QScrollBar(Qt::Vertical, nullptr);
	QScrollArea* typeScrollArea = new QScrollArea;
	typeScrollArea->setWidget(typeBrowser);
	typeScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	typeScrollArea->setWidgetResizable(true);
	typeScrollArea->setVerticalScrollBar(typeSideBar);
	typeScrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	typeLayout->addWidget(typeScrollArea);
	typeLayout->setStretchFactor(typeScrollArea, 10);
	bodyLayout->addLayout(typeLayout);
	bodyLayout->setStretchFactor(typeLayout, 1);

	//sequence browser
	QVBoxLayout* sequenceLayout = new QVBoxLayout;
	sequenceLayout->setContentsMargins(5, 5, 5, 5);
	sequenceLayout->setSpacing(10);

	QLabel* sequenceLabel = new QLabel("Sequence Browser", body_);
	sequenceLabel->setProperty(::widgetTitleProperty, true);
	sequenceLabel->setMinimumWidth(300);
	sequenceLabel->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	sequenceLayout->addWidget(sequenceLabel, 1, Qt::AlignHCenter);
	sequenceLayout->setStretchFactor(sequenceLabel, 1);


	SequenceBrowser* sequenceBrowser = new SequenceBrowser(body_);
	QScrollBar* sequenceSideBar = new QScrollBar(Qt::Vertical, nullptr);
	QScrollArea* sequenceScrollArea = new QScrollArea;
	sequenceScrollArea->setWidget(sequenceBrowser);
	sequenceScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	sequenceScrollArea->setWidgetResizable(true);
	sequenceScrollArea->setVerticalScrollBar(sequenceSideBar);

	sequenceScrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	sequenceLayout->addWidget(sequenceScrollArea);
	sequenceLayout->setStretchFactor(sequenceScrollArea, 10);
	bodyLayout->addLayout(sequenceLayout);
	bodyLayout->setStretchFactor(sequenceLayout, 1);
	bodyLayout->setStretchFactor(sequenceScrollArea, 1);

	//result browser
	/*QVBoxLayout* resultLayout = new QVBoxLayout;
	resultLayout->setContentsMargins(5, 5, 5, 5);
	resultLayout->setSpacing(10);

	QLabel* resultLabel = new QLabel("Result Browser", body_);
	resultLabel->setProperty(::widgetTitleProperty, true);
	resultLabel->setMinimumWidth(300);
	resultLabel->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	resultLayout->addWidget(resultLabel, 1, Qt::AlignHCenter);
	resultLayout->setStretchFactor(resultLabel, 1);

	ResultBrowser* resultBrowser = new ResultBrowser(body_);
	QScrollBar* resultSideBar = new QScrollBar(Qt::Vertical, nullptr);
	QScrollArea* resultScrollArea = new QScrollArea;
	resultScrollArea->setWidget(resultBrowser);
	resultScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	resultScrollArea->setWidgetResizable(true);
	resultScrollArea->setVerticalScrollBar(resultSideBar);
	resultScrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	resultLayout->addWidget(resultScrollArea);
	resultLayout->setStretchFactor(resultScrollArea, 10);
	bodyLayout->addLayout(resultLayout);
	bodyLayout->setStretchFactor(resultLayout, 1);*/



	//packet details widget
	PacketDetails* packetDetails = new PacketDetails(body_);
	sequenceBrowser->packetDetails = packetDetails;
	bodyLayout->addWidget(packetDetails);
	bodyLayout->setStretchFactor(packetDetails, 2);

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