#include "packet_details_widget.h"



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
void PacketDetails::viewMemRead32() {
	/*CustomLineEdit* lineEdit = new CustomLineEdit( "Address",100,50,"content",this);
	contentLayout_->addWidget(lineEdit);
	currentLineEdits.push_back(lineEdit);*/

	//header
	QHBoxLayout* headerLayout = new QHBoxLayout(this);
	CustomLineEdit* type = new CustomLineEdit("Type", 100, 50, QString::number(static_cast<int>(TLPType::MemRead32), 2).rightJustified(8, '0'), this);
	headerLayout->addWidget(type);
	CustomLineEdit* tc = new CustomLineEdit("TC", 100,50, "000", this);
	headerLayout->addWidget(tc);
	CustomLineEdit* ohc = new CustomLineEdit("OHC", 100,50, "00001", this);
	headerLayout->addWidget(ohc);
	CustomLineEdit* ts = new CustomLineEdit("TS", 100,50, "000", this);
	headerLayout->addWidget(ts);
	CustomLineEdit* attr = new CustomLineEdit("Attr", 100,50, "000", this);
	headerLayout->addWidget(attr);
	CustomLineEdit* length = new CustomLineEdit("Length", 100,50, "00000000000", this);
	headerLayout->addWidget(length);
	contentLayout_->addLayout(headerLayout);

	QHBoxLayout* secondDwLayout = new QHBoxLayout(this);
	CustomLineEdit* requesterId = new CustomLineEdit("Requester ID", 100,50, "0000000000000", this);
	secondDwLayout->addWidget(requesterId);
	CustomLineEdit* ep = new CustomLineEdit("EP", 100, 50, "0", this);
	secondDwLayout->addWidget(ep);
	CustomLineEdit* reserved = new CustomLineEdit("R", 100, 50, "", this);
	secondDwLayout->addWidget(reserved);
	NonHeaderBase* nonbase = currentTLP->header->nonBase;
	AddressRouting32Bit* addressRouting = dynamic_cast<AddressRouting32Bit*>(nonbase);
	CustomLineEdit* tag = new CustomLineEdit("Tag", 100, 50, QString::number(static_cast<int>(addressRouting->tag), 2), this);
	secondDwLayout->addWidget(tag);
	contentLayout_->addLayout(secondDwLayout);

	QHBoxLayout* thirdDwLayout = new QHBoxLayout(this);
	CustomLineEdit* address = new CustomLineEdit("Address", 100, 50, QString::number(static_cast<int>(addressRouting->address), 2), this);
	thirdDwLayout->addWidget(address);
	CustomLineEdit* at = new CustomLineEdit("AT", 100, 50, "000", this);
	thirdDwLayout->addWidget(at);
	contentLayout_->addLayout(thirdDwLayout);

	QHBoxLayout* fourthDwLayout = new QHBoxLayout(this);
	CustomLineEdit* nw = new CustomLineEdit("NW", 100, 50, "000", this);
	fourthDwLayout->addWidget(nw);
	CustomLineEdit* pv = new CustomLineEdit("PV", 100, 50, "000", this);
	fourthDwLayout->addWidget(pv);
	CustomLineEdit* pmr = new CustomLineEdit("PMR", 100, 50, "000", this);
	fourthDwLayout->addWidget(pmr);
	CustomLineEdit* pasid = new CustomLineEdit("PASID", 100, 50, "0000000000000000", this);
	fourthDwLayout->addWidget(pasid);
	contentLayout_->addLayout(fourthDwLayout);
	OHC* ohcElement = currentTLP->header->OHCVector[0];
	OHCA1 * ohca1 = dynamic_cast<OHCA1*>(ohcElement);
	CustomLineEdit* firstDWBE = new CustomLineEdit("First DW BE", 100, 50, QString::fromStdString(ohca1->firstDWBE.to_string()), this);
	fourthDwLayout->addWidget(firstDWBE);
	CustomLineEdit* lastDWBE = new CustomLineEdit("Last DW BE", 100, 50, QString::fromStdString(ohca1->lastDWBE.to_string()), this);
	fourthDwLayout->addWidget(lastDWBE);
	contentLayout_->addLayout(fourthDwLayout);

	currentLineEdits.push_back(address);
	currentLineEdits.push_back(firstDWBE);
	currentLineEdits.push_back(lastDWBE);



	
}
void PacketDetails::viewMemRead64() {
	/*CustomLineEdit* lineEdit = new CustomLineEdit( "Address",100,50,"content",this);
	contentLayout_->addWidget(lineEdit);
	currentLineEdits.push_back(lineEdit);*/

	//header
	QHBoxLayout* headerLayout = new QHBoxLayout(this);
	CustomLineEdit* type = new CustomLineEdit("Type", 100, 50, QString::number(static_cast<int>(TLPType::MemRead32), 2).rightJustified(8, '0'), this);
	headerLayout->addWidget(type);
	CustomLineEdit* tc = new CustomLineEdit("TC", 100, 50, "000", this);
	headerLayout->addWidget(tc);
	CustomLineEdit* ohc = new CustomLineEdit("OHC", 100, 50, "00001", this);
	headerLayout->addWidget(ohc);
	CustomLineEdit* ts = new CustomLineEdit("TS", 100, 50, "000", this);
	headerLayout->addWidget(ts);
	CustomLineEdit* attr = new CustomLineEdit("Attr", 100, 50, "000", this);
	headerLayout->addWidget(attr);
	CustomLineEdit* length = new CustomLineEdit("Length", 100, 50, "00000000000", this);
	headerLayout->addWidget(length);
	contentLayout_->addLayout(headerLayout);

	QHBoxLayout* secondDwLayout = new QHBoxLayout(this);
	CustomLineEdit* requesterId = new CustomLineEdit("Requester ID", 100, 50, "0000000000000", this);
	secondDwLayout->addWidget(requesterId);
	CustomLineEdit* ep = new CustomLineEdit("EP", 100, 50, "0", this);
	secondDwLayout->addWidget(ep);
	CustomLineEdit* reserved = new CustomLineEdit("R", 100, 50, "", this);
	secondDwLayout->addWidget(reserved);
	NonHeaderBase* nonbase = currentTLP->header->nonBase;
	AddressRouting64Bit* addressRouting = dynamic_cast<AddressRouting64Bit*>(nonbase);
	CustomLineEdit* tag = new CustomLineEdit("Tag", 100, 50, QString::number(static_cast<int>(addressRouting->tag), 2), this);
	secondDwLayout->addWidget(tag);
	contentLayout_->addLayout(secondDwLayout);

	QHBoxLayout* thirdDwLayout = new QHBoxLayout(this);
	CustomLineEdit* address = new CustomLineEdit("Address", 100, 50, QString::number(static_cast<int>(addressRouting->address), 2), this);
	thirdDwLayout->addWidget(address);
	CustomLineEdit* at = new CustomLineEdit("AT", 100, 50, "000", this);
	thirdDwLayout->addWidget(at);
	contentLayout_->addLayout(thirdDwLayout);

	QHBoxLayout* tDwLayout = new QHBoxLayout(this);
	CustomLineEdit* ffyuuf= new CustomLineEdit("doiffferereet", 100, 50, QString::number(46), this);
	tDwLayout->addWidget(ffyuuf);
	contentLayout_->addLayout(tDwLayout);

	QHBoxLayout* fourthDwLayout = new QHBoxLayout(this);
	CustomLineEdit* nw = new CustomLineEdit("NW", 100, 50, "000", this);
	fourthDwLayout->addWidget(nw);
	CustomLineEdit* pv = new CustomLineEdit("PV", 100, 50, "000", this);
	fourthDwLayout->addWidget(pv);
	CustomLineEdit* pmr = new CustomLineEdit("PMR", 100, 50, "000", this);
	fourthDwLayout->addWidget(pmr);
	CustomLineEdit* pasid = new CustomLineEdit("PASID", 100, 50, "0000000000000000", this);
	fourthDwLayout->addWidget(pasid);
	contentLayout_->addLayout(fourthDwLayout);
	OHC* ohcElement = currentTLP->header->OHCVector[0];
	OHCA1* ohca1 = dynamic_cast<OHCA1*>(ohcElement);
	CustomLineEdit* firstDWBE = new CustomLineEdit("First DW BE", 100, 50, QString::fromStdString(ohca1->firstDWBE.to_string()), this);
	fourthDwLayout->addWidget(firstDWBE);
	CustomLineEdit* lastDWBE = new CustomLineEdit("Last DW BE", 100, 50, QString::fromStdString(ohca1->lastDWBE.to_string()), this);
	fourthDwLayout->addWidget(lastDWBE);
	contentLayout_->addLayout(fourthDwLayout);

	currentLineEdits.push_back(address);
	currentLineEdits.push_back(firstDWBE);
	currentLineEdits.push_back(lastDWBE);




}

void PacketDetails::updateView(TLP* tlp) {
	// Updates the view with the new TLP if the TLP is different from the current one
	/*if (tlp == currentTLP) {
		return;
	}*/
	clearView(contentLayout_);
	currentTLP = tlp;
	currentLineEdits.clear();
	if(tlp->header->TLPtype == TLPType::MemRead32){
		viewMemRead32();

	}
	else if (tlp->header->TLPtype == TLPType::MemRead64) {
		viewMemRead64();

	}
	else {
		//place holder
		QLabel* label = new QLabel(QString("TLPCard details"), this);
		contentLayout_->addWidget(label);
	}
	
}

void PacketDetails::clearView(QLayout* layout) {
	// Removes any existing content from the view
	QLayoutItem* child;
	while ((child = contentLayout_->takeAt(0)) != nullptr) {
		if (child->widget() != saveButton) {
			delete child->widget();
			delete child;
		}
		
	}
	
}
int binaryToInteger(const std::string& binary) {
	int result = 0;
	for (int i = 0; i <= binary.size() - 1; i++) {
		result *= 2;
		result += binary[i] - '0';
	}
	return result;
}


void PacketDetails::saveValues() {
	////place holder
	//QLabel* savedlabel = new QLabel(QString("Values saved"), this);
	//contentLayout_->addWidget(savedlabel);
	if (currentTLP->header->TLPtype == TLPType::MemRead32) {
		AddressRouting32Bit* addressRouting = dynamic_cast<AddressRouting32Bit*>(currentTLP->header->nonBase);
		addressRouting->address = binaryToInteger(currentLineEdits[0]->lineEdit->text().toStdString());
		OHCA1* ohca1 = dynamic_cast<OHCA1*>(currentTLP->header->OHCVector[0]);
		ohca1->firstDWBE = std::bitset<4>(currentLineEdits[1]->lineEdit->text().toStdString());
		ohca1->lastDWBE = std::bitset<4>(currentLineEdits[2]->lineEdit->text().toStdString());
	}
	else
	{
		//place holder
		QLabel* savedlabel = new QLabel(QString("Values saved"), this);
		contentLayout_->addWidget(savedlabel);
	}
}

void PacketDetails:: manageLayout() {
	contentLayout_->setContentsMargins(0, 0, 0, 0);
	contentLayout_->setSpacing(10);

	saveButton = new QPushButton("Save",this);

	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveValues()));

	//make the button at the bottom
	contentLayout_->addStretch();

	contentLayout_->addWidget(saveButton);
	setLayout(contentLayout_);

	
}