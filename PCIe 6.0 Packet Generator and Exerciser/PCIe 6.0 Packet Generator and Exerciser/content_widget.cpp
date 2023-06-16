#include "content_widget.h"
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QApplication>
#include "sequence_browser.h"
#include "type_browser.h"
#include "result_browser.h"
#include"packet_details_widget.h"
#include"config_space_widget.h"
#include "type1_config_space/type1_config.h"

namespace {
	constexpr char sequenceExplorerLabel[] = "Sequence Explorer";
	constexpr char resultExplorerLabel[] = "Result Explorer";
	constexpr char headerFrameProperty[] = "headerFrame";
	constexpr char centralTitleProperty[] = "centralTitle";
	constexpr char widgetTitleProperty[] = "widgetTitle";
	constexpr char submitButtonProperty[] = "submitButton";
	constexpr char selectedTabProperty[] = "selectedTab";
	constexpr char unselectedTabProprety[] = "unselectedTab";
	constexpr char unselectedTabStyleString[] = "background-color:#45aff8; color:white; font-size: 15px;";
	constexpr char selectedTabStyleString[] = "background-color: white; color: #45aff8; font-size: 15px;";
	constexpr int titleLabelWidth = 200;
}
using namespace Ui;

ContentWidget::ContentWidget(QWidget* parent,
			QueueWrapper<TLP*>* rootComplexToLayers,
			QueueWrapper<TLP*>* layersToRootComplex)
	: QFrame(parent),
	rootComplexToLayers_(rootComplexToLayers),
	layersToRootComplex_(layersToRootComplex)
{
	type1Config_ = Type1Config::constructType1ConfigSpace();
	createHeader();
	createBody();
	createFooter();
	manageLayout();
}

ContentWidget::~ContentWidget()
{

}


void ContentWidget::createHeader() 
{
	createResultExplorerTab();
	createSequenceExplorerTab();
	header_ = new QFrame(this);
	header_->setProperty(::headerFrameProperty, true);
	QLabel* titleLabel = new QLabel("PCIe 6.0 Packet Generator and Exerciser", header_);
	titleLabel->setProperty(::centralTitleProperty, true);
	titleLabel->setAlignment(Qt::AlignCenter);
	QVBoxLayout* headerLayout = new QVBoxLayout;
	headerLayout->setContentsMargins(0, 0, 0, 0);
	headerLayout->setSpacing(0);
	headerLayout->addWidget(titleLabel);

	QHBoxLayout* tabsLayout = new QHBoxLayout;
	tabsLayout->addWidget(sequenceExplorerTab_, Qt::AlignLeft);
	tabsLayout->addWidget(resultExplorerTab_, Qt::AlignLeft);
	QWidget* horizontalSpacer = new QWidget;
	horizontalSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	tabsLayout->addWidget(horizontalSpacer);

	headerLayout->addLayout(tabsLayout);
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
	typeLabel->setMinimumWidth(::titleLabelWidth);
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
	typeFrame_ = new QFrame(this);
	typeFrame_->setLayout(typeLayout);
	bodyLayout->addWidget(typeFrame_);
	bodyLayout->setStretchFactor(typeFrame_, 1);

	//sequence browser
	QVBoxLayout* sequenceLayout = new QVBoxLayout;
	sequenceLayout->setContentsMargins(5, 5, 5, 5);
	sequenceLayout->setSpacing(10);

	QLabel* sequenceLabel = new QLabel("Sequence Browser", body_);
	sequenceLabel->setProperty(::widgetTitleProperty, true);
	sequenceLabel->setMinimumWidth(::titleLabelWidth);
	sequenceLabel->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	sequenceLayout->addWidget(sequenceLabel, 1, Qt::AlignHCenter);
	sequenceLayout->setStretchFactor(sequenceLabel, 1);


	sequenceBrowser_ = new SequenceBrowser(body_);
	QScrollBar* sequenceSideBar = new QScrollBar(Qt::Vertical, nullptr);
	QScrollArea* sequenceScrollArea = new QScrollArea;
	sequenceScrollArea->setWidget(sequenceBrowser_);
	sequenceScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	sequenceScrollArea->setWidgetResizable(true);
	sequenceScrollArea->setVerticalScrollBar(sequenceSideBar);

	sequenceScrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	/*QGraphicsDropShadowEffect* sequenceShadowEffect = new QGraphicsDropShadowEffect;
	sequenceShadowEffect->setBlurRadius(30);
	sequenceShadowEffect->setOffset(0, 0);
	sequenceShadowEffect->setColor(Qt::black);

	sequenceScrollArea->setGraphicsEffect(sequenceShadowEffect);*/
	
	sequenceLayout->addWidget(sequenceScrollArea);
	sequenceLayout->setStretchFactor(sequenceScrollArea, 10);
	QFrame* sequenceFrame = new QFrame(this);
	sequenceFrame->setLayout(sequenceLayout);
	bodyLayout->addWidget(sequenceFrame);
	bodyLayout->setStretchFactor(sequenceFrame, 1);

	//result browser
	QVBoxLayout* resultBrowserLayout = new QVBoxLayout;
	resultBrowserLayout->setContentsMargins(5, 5, 5, 5);
	resultBrowserLayout->setSpacing(10);

	QLabel* resultLabel = new QLabel("Result Browser", body_);
	resultLabel->setProperty(::widgetTitleProperty, true);
	resultLabel->setMinimumWidth(300);
	resultLabel->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
	resultBrowserLayout->addWidget(resultLabel, 1, Qt::AlignHCenter);
	resultBrowserLayout->setStretchFactor(resultLabel, 1);

	resultBrowser_ = new ResultBrowser(body_);
	QScrollBar* resultSideBar = new QScrollBar(Qt::Vertical, nullptr);
	QScrollArea* resultScrollArea = new QScrollArea;
	resultScrollArea->setWidget(resultBrowser_);
	resultScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	resultScrollArea->setWidgetResizable(true);
	resultScrollArea->setVerticalScrollBar(resultSideBar);
	resultScrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	resultBrowserLayout->addWidget(resultScrollArea);
	resultBrowserLayout->setStretchFactor(resultScrollArea, 10);

	resultFrame_ = new QFrame(this);
	resultFrame_->setLayout(resultBrowserLayout);
	bodyLayout->addWidget(resultFrame_);
	bodyLayout->setStretchFactor(resultFrame_, 1);
	resultFrame_->setVisible(false);


	//packet details widget
	PacketDetails* packetDetails = new PacketDetails(body_);
	sequenceBrowser_->packetDetails = packetDetails;
	bodyLayout->addWidget(packetDetails);
	bodyLayout->setStretchFactor(packetDetails, 2);


	


	
	bodyLayout->setStretchFactor(packetDetails, 2);

	body_->setLayout(bodyLayout);

	connect (sequenceSideBar, SIGNAL(valueChanged(int)), resultSideBar, SLOT(setValue(int)));
	connect (resultSideBar, SIGNAL(valueChanged(int)), sequenceSideBar, SLOT(setValue(int)));
}
//createFooter
void ContentWidget::createFooter()
{
	footer_ = new QFrame(this);
	createSubmitButton();
	createConfigSpaceButton();
	QVBoxLayout* footerLayout = new QVBoxLayout;
	footerLayout->setContentsMargins(100, 10, 100, 20);
	footerLayout->setSpacing(0);
	footerLayout->addWidget(submitButton_);
	footerLayout->setAlignment(submitButton_, Qt::AlignRight);

	footerLayout->addWidget(configSpaceButton_);
	footerLayout->setAlignment(configSpaceButton_, Qt::AlignLeft);
	footer_->setLayout(footerLayout);
}
void ContentWidget::createConfigSpaceButton()
{
	configSpaceButton_ = new QPushButton("Config Space", this);
	configSpaceButton_->setMinimumWidth(200);
	configSpaceButton_->setMinimumHeight(30);
	configSpaceButton_->setMaximumWidth(400);
	configSpaceButton_->setMaximumHeight(50);
	configSpaceButton_->setContentsMargins(100, 50, 100, 100);

	connect(configSpaceButton_, SIGNAL(clicked()), this, SLOT(onConfigSpaceButtonClick()));
}
void ContentWidget::createSubmitButton()
{
	submitButton_ = new QPushButton("Submit", this);
	submitButton_->setMinimumWidth(200);
	submitButton_->setMinimumHeight(30);
	submitButton_->setMaximumWidth(400);
	submitButton_->setMaximumHeight(50);
	submitButton_->setContentsMargins(100, 50, 100, 100);
	submitButton_->setProperty(::submitButtonProperty, true);

	connect(submitButton_, SIGNAL(clicked()), this, SLOT(onSubmitButtonClick()));
}

void ContentWidget::createSequenceExplorerTab() {
	sequenceExplorerTab_ = new QPushButton(::sequenceExplorerLabel, this);
	//sequenceExplorerTab_->setMinimumWidth(100);
	//sequenceExplorerTab_->setMinimumHeight(30);
	sequenceExplorerTab_->setMaximumWidth(150);
	sequenceExplorerTab_->setMaximumHeight(30);
	sequenceExplorerTab_->setProperty(::selectedTabProperty, true);
	connect(sequenceExplorerTab_, SIGNAL(clicked()), this, SLOT(onSequenceExplorerTabClick()));
}

void ContentWidget::createResultExplorerTab() {
	resultExplorerTab_ = new QPushButton(::resultExplorerLabel, this);
	//resultExplorerTab_->setMinimumWidth(100);
	//resultExplorerTab_->setMinimumHeight(30);
	resultExplorerTab_->setMaximumWidth(150);
	resultExplorerTab_->setMaximumHeight(30);
	resultExplorerTab_->setProperty(::unselectedTabProprety, true);
	connect(resultExplorerTab_, SIGNAL(clicked()), this, SLOT(onResultExplorerTabClick()));
}


void ContentWidget::manageLayout() 
{
	QVBoxLayout* contentLayout = new QVBoxLayout;
	contentLayout->setContentsMargins(0, 0, 0, 0);
	contentLayout->setSpacing(0);
	contentLayout->addWidget(header_);
	contentLayout->setStretchFactor(header_, 4);
	contentLayout->addWidget(body_);
	contentLayout->setStretchFactor(body_, 32);
	contentLayout->addWidget(footer_);
	contentLayout->setStretchFactor(footer_, 1);

	setLayout(contentLayout);
}

void ContentWidget::onSubmitButtonClick() {
	rootComplexToLayers_->push(sequenceBrowser_->getTLPCards());

	//****Uncomment this to see the result when the layers are connected to the root complex****
	//std::queue<TLP*> resultPackets = layersToRootComplex_->popAll();

	typeFrame_->setVisible(false);
	resultFrame_->setVisible(true);
	sequenceExplorerTab_->setStyleSheet(::unselectedTabStyleString);
	resultExplorerTab_->setStyleSheet(::selectedTabStyleString);
	sequenceBrowser_->setCurrentTab(currentTab::resultExplorer);
	sequenceBrowser_->setAcceptDrops(false);

}

void ContentWidget::onSequenceExplorerTabClick() {
	typeFrame_->setVisible(true);
	resultFrame_->setVisible(false);
	sequenceExplorerTab_->setStyleSheet(::selectedTabStyleString);
	resultExplorerTab_->setStyleSheet(::unselectedTabStyleString);
	sequenceBrowser_->setCurrentTab(currentTab::sequenceExplorer);
	sequenceBrowser_->setAcceptDrops(true);
}

void ContentWidget::onResultExplorerTabClick() {
	typeFrame_->setVisible(false);
	resultFrame_->setVisible(true);
	sequenceExplorerTab_->setStyleSheet(::unselectedTabStyleString);
	resultExplorerTab_->setStyleSheet(::selectedTabStyleString);
	sequenceBrowser_->setCurrentTab(currentTab::resultExplorer);
	sequenceBrowser_->setAcceptDrops(false);
}

void ContentWidget::onConfigSpaceButtonClick() {
	ConfigSpaceWidget* configSpaceWidget = new ConfigSpaceWidget(type1Config_, nullptr);
	configSpaceWidget->show();
}