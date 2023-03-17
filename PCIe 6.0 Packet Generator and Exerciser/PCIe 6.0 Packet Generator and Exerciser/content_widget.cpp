#include "content_widget.h"
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QGraphicsDropShadowEffect>

#include "sequence_browser.h"
#include "type_browser.h"

namespace {
	constexpr char headerFrameProperty[] = "headerFrame";
	constexpr char centralTitleProperty[] = "centralTitle";
	constexpr char widgetTitleProperty[] = "widgetTitle";
	constexpr char submitButtonProperty[] = "submitButton";
	constexpr int titleLabelWidth = 200;
}
using namespace Ui;

ContentWidget::ContentWidget(QWidget* parent)
	: QFrame(parent)
{
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
	bodyLayout->addLayout(typeLayout);
	bodyLayout->setStretchFactor(typeLayout, 1);

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


	SequenceBrowser* sequenceBrowser = new SequenceBrowser(body_);
	QScrollBar* sequenceSideBar = new QScrollBar(Qt::Vertical, nullptr);
	QScrollArea* sequenceScrollArea = new QScrollArea;
	sequenceScrollArea->setWidget(sequenceBrowser);
	sequenceScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	sequenceScrollArea->setWidgetResizable(true);
	sequenceScrollArea->setVerticalScrollBar(sequenceSideBar);

	sequenceScrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

	QGraphicsDropShadowEffect* sequenceShadowEffect = new QGraphicsDropShadowEffect;
	sequenceShadowEffect->setBlurRadius(30);
	sequenceShadowEffect->setOffset(0, 0);
	sequenceShadowEffect->setColor(Qt::black);

	sequenceScrollArea->setGraphicsEffect(sequenceShadowEffect);

	sequenceLayout->addWidget(sequenceScrollArea);
	sequenceLayout->setStretchFactor(sequenceScrollArea, 10);
	bodyLayout->addLayout(sequenceLayout);
	bodyLayout->setStretchFactor(sequenceLayout, 1);
	bodyLayout->setStretchFactor(sequenceScrollArea, 1);

	body_->setLayout(bodyLayout);
}
//createFooter
void ContentWidget::createFooter()
{
	footer_ = new QFrame(this);
	createSubmitButton();
	QVBoxLayout* footerLayout = new QVBoxLayout;
	footerLayout->setContentsMargins(100, 10, 100, 20);
	footerLayout->setSpacing(0);
	footerLayout->addWidget(submitButton_);
	footerLayout->setAlignment(submitButton_, Qt::AlignRight);
	footer_->setLayout(footerLayout);
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

	//setStyleSheet("border: red 2px solid;");
}