#include "packet_details_widget.h"
#include <unordered_map>


using namespace Ui;

PacketDetails::PacketDetails(QWidget* parent)
	: QFrame(parent)

{
	contentLayout_ = new QVBoxLayout;
	detailsLayout_ = new QGridLayout;
	manageLayout();
}
PacketDetails::~PacketDetails()
{
}
long long PacketDetails::combineAddresses(std::string upperAddress, std::string lowerAddress) {
	// Convert the upper and lower addresses to integers.
	int upperAddressInt = binaryToInteger(upperAddress);
	int lowerAddressInt = binaryToInteger(lowerAddress);

	// Combine the upper and lower addresses into a long long address.
	long long address = (long long)upperAddressInt << 32 | (long long)lowerAddressInt;

	return address;
}
int PacketDetails::binaryToInteger(const std::string& binary) {
	int result = 0;
	for (int i = 0; i <= binary.size() - 1; i++) {
		result *= 2;
		result += binary[i] - '0';
	}
	return result;
}
void PacketDetails::createHeader() {
	
	CustomLineEdit* type = new CustomLineEdit("Type", 100, 50, QString::number(static_cast<int>(currentTLP->header->TLPtype), 2).rightJustified(8, '0'), this);
	detailsLayout_->addWidget(type,0,0);
	CustomLineEdit* tc = new CustomLineEdit("TC", 100, 50, "000", this);
	detailsLayout_->addWidget(tc,0,1);
	CustomLineEdit* ohc = new CustomLineEdit("OHC", 100, 50, "00001", this);
	detailsLayout_->addWidget(ohc,0,2);
	CustomLineEdit* ts = new CustomLineEdit("TS", 100, 50, "000", this);
	detailsLayout_->addWidget(ts,0,3);
	CustomLineEdit* attr = new CustomLineEdit("Attr", 100, 50, "000", this);
	detailsLayout_->addWidget(attr,0,4);
	CustomLineEdit* length = new CustomLineEdit("Length", 100, 50, QString::number(static_cast<int>(currentTLP->header->lengthInDoubleWord), 2).rightJustified(10, '0'), this);
	detailsLayout_->addWidget(length,0,5);
}
void PacketDetails::createMem32bCommon() {
	//creates the second dw in memory requests 32bit
	
	CustomLineEdit* requesterId = new CustomLineEdit("Requester ID", 100, 50, "0000000000000", this);
	detailsLayout_->addWidget(requesterId, 1,0);
	CustomLineEdit* ep = new CustomLineEdit("EP", 100, 50, "0", this);
	detailsLayout_->addWidget(ep,1,1);
	CustomLineEdit* reserved = new CustomLineEdit("R", 100, 50, "", this);
	detailsLayout_->addWidget(reserved,1,2);
	NonHeaderBase* nonbase = currentTLP->header->nonBase;
	AddressRouting32Bit* addressRouting = dynamic_cast<AddressRouting32Bit*>(nonbase);
	CustomLineEdit* tag = new CustomLineEdit("Tag", 100, 50, QString::number(static_cast<int>(addressRouting->tag), 2), this);
	detailsLayout_->addWidget(tag,1,3);

	//address
	CustomLineEdit* address = new CustomLineEdit("Address", 100, 50, QString::number(static_cast<int>(addressRouting->address), 2).rightJustified(30, '0'), this, false);
	detailsLayout_->addWidget(address,2,0);
	CustomLineEdit* at = new CustomLineEdit("AT", 100, 50, "000", this);
	detailsLayout_->addWidget(at,2,1);

	//saving to CurrentLineEdits
	lineEditsMap["address"] = address;
	

	

}

void PacketDetails::createMem64bCommon() {
	//creates the second dw in memory requests 64bit

	CustomLineEdit* requesterId = new CustomLineEdit("Requester ID", 100, 50, "0000000000000", this);
	detailsLayout_->addWidget(requesterId, 1, 0);
	CustomLineEdit* ep = new CustomLineEdit("EP", 100, 50, "0", this);
	detailsLayout_->addWidget(ep, 1, 1);
	CustomLineEdit* reserved = new CustomLineEdit("R", 100, 50, "", this);
	detailsLayout_->addWidget(reserved, 1, 2);
	NonHeaderBase* nonbase = currentTLP->header->nonBase;
	AddressRouting64Bit* addressRouting = dynamic_cast<AddressRouting64Bit*>(nonbase);
	CustomLineEdit* tag = new CustomLineEdit("Tag", 100, 50, QString::number(static_cast<int>(addressRouting->tag), 2), this);
	detailsLayout_->addWidget(tag, 1, 3);

	//address
	int upperAddressValue = (int)(addressRouting->address >> 32);
	CustomLineEdit* upperAddress = new CustomLineEdit("Address[63:32]", 100, 50, QString::number(static_cast<int>(upperAddressValue), 2).rightJustified(32, '0'), this, false);
	detailsLayout_->addWidget(upperAddress, 2, 0);
	int lowerAddressValue = (int)addressRouting->address & 0xFFFFFFFF;
	CustomLineEdit* lowerAddress = new CustomLineEdit("Address[31:2]", 100, 50, QString::number(static_cast<long long>(lowerAddressValue), 2).rightJustified(30, '0'), this,false);
	detailsLayout_->addWidget(lowerAddress, 3, 0);
	CustomLineEdit* at = new CustomLineEdit("AT", 100, 50, "000", this);
	detailsLayout_->addWidget(at, 3, 1);

	//saving to address CurrentLineEdits
	lineEditsMap["upperAddress"] = upperAddress;
	lineEditsMap["lowerAddress"] = lowerAddress;


}
void PacketDetails::createCongigOHCvector() {
	//OHC
	OHC* ohcElement = currentTLP->header->OHCVector[0];
	OHCA3* ohca3 = dynamic_cast<OHCA3*>(ohcElement);
	CustomLineEdit* destination = new CustomLineEdit("Destination Segment", 100, 50, QString::number(ohca3->destinationSegment,2), this,false);
	detailsLayout_->addWidget(destination,3, 0);
	

	detailsLayout_->addWidget(new CustomLineEdit("R", 100, 50, "", this), 3, 1);
	detailsLayout_->addWidget(new CustomLineEdit("DSV", 100, 50, "0", this), 3, 2);
	detailsLayout_->addWidget(new CustomLineEdit("R", 100, 50, "", this), 3, 3);
	
	CustomLineEdit* firstDWBE = new CustomLineEdit("First DW BE", 100, 50, QString::fromStdString(ohca3->firstDWBE.to_string()), this, false);
	detailsLayout_->addWidget(firstDWBE, 3, 4);
	CustomLineEdit* lastDWBE = new CustomLineEdit("Last DW BE", 100, 50, QString::fromStdString(ohca3->lastDWBE.to_string()), this, false);
	detailsLayout_->addWidget(lastDWBE, 3, 5);


	//saving to currentLineEdits
	lineEditsMap["destinationSegment"] = destination;
	lineEditsMap["firstDWBE"] = firstDWBE;
	lineEditsMap["lastDWBE"] = lastDWBE;
}


void PacketDetails::createMemOHCvector(int row) {
	//OHC
	CustomLineEdit* nw = new CustomLineEdit("NW", 100, 50, "000", this);
	detailsLayout_->addWidget(nw,row,0);
	CustomLineEdit* pv = new CustomLineEdit("PV", 100, 50, "000", this);
	detailsLayout_->addWidget(pv,row,1);
	CustomLineEdit* pmr = new CustomLineEdit("PMR", 100, 50, "000", this);
	detailsLayout_->addWidget(pmr,row,2);
	CustomLineEdit* pasid = new CustomLineEdit("PASID", 100, 50, "0000000000000000", this);
	detailsLayout_->addWidget(pasid,row,3);

	OHC* ohcElement = currentTLP->header->OHCVector[0];
	OHCA1* ohca1 = dynamic_cast<OHCA1*>(ohcElement);
	CustomLineEdit* firstDWBE = new CustomLineEdit("First DW BE", 100, 50, QString::fromStdString(ohca1->firstDWBE.to_string()), this, false);
	detailsLayout_->addWidget(firstDWBE,row,4);
	CustomLineEdit* lastDWBE = new CustomLineEdit("Last DW BE", 100, 50, QString::fromStdString(ohca1->lastDWBE.to_string()), this, false);
	detailsLayout_->addWidget(lastDWBE,row,5);


	//saving to currentLineEdits
	lineEditsMap["firstDWBE"] = firstDWBE;
	lineEditsMap["lastDWBE"] = lastDWBE;


}


void PacketDetails::createDataPayload(int row) {
	
	
	string dataString;
	boost::to_string(currentTLP->dataPayload, dataString);
	CustomLineEdit* data = new CustomLineEdit("Data", 100, 50, QString::fromStdString(dataString), this, false);
	detailsLayout_->addWidget(data,row,0);

	//saving to current LineEdits map 
	lineEditsMap["dataPayload"] = data;
}
void PacketDetails::viewMemRead32() {

	//header
	createHeader();
	createMem32bCommon();
	createMemOHCvector(3);

}
void PacketDetails::viewMemRead64() {
	
	createHeader();
	createMem64bCommon();
	createMemOHCvector(4);

}
void PacketDetails::viewMemWrite32() {


	//header
	createHeader();
	createMem32bCommon();
	createMemOHCvector(3);
	createDataPayload(4);


}
void PacketDetails::viewMemWrite64() {

	createHeader();
	createMem64bCommon();
	createMemOHCvector(4);
	createDataPayload(5);
}
void PacketDetails::createConfigCommon() {
	CustomLineEdit* requesterId = new CustomLineEdit("Requester ID", 100, 50, "0000000000000", this);
	detailsLayout_->addWidget(requesterId, 1, 0);
	CustomLineEdit* ep = new CustomLineEdit("EP", 100, 50, "0", this);
	detailsLayout_->addWidget(ep, 1, 1);
	
	detailsLayout_->addWidget(new CustomLineEdit("R", 100, 50, "", this), 1, 2);
	NonHeaderBase* nonbase = currentTLP->header->nonBase;
	ConfigNonHeaderBase* configNonBase = dynamic_cast<ConfigNonHeaderBase*>(nonbase);
	CustomLineEdit* tag = new CustomLineEdit("Tag", 100, 50, QString::number(static_cast<int>(configNonBase->tag), 2), this);
	detailsLayout_->addWidget(tag, 1, 3);

	//bdf and register
	CustomLineEdit* busNumber = new CustomLineEdit("Bus Number", 100, 50, QString::number(static_cast<int>(configNonBase->busNumber),2), this);
	detailsLayout_->addWidget(busNumber, 2, 0);
	CustomLineEdit* deviceNumber = new CustomLineEdit("Device Number", 100, 50, QString::number(static_cast<int>(configNonBase->deviceNumber), 2), this);
	detailsLayout_->addWidget(deviceNumber, 2, 1);
	CustomLineEdit* functionNumber = new CustomLineEdit("Function Number", 100, 50, QString::number(static_cast<int>(configNonBase->functionNumber), 2), this);
	detailsLayout_->addWidget(functionNumber, 2, 2);
	
	detailsLayout_->addWidget(new CustomLineEdit("R", 100, 50, "", this), 2, 3);
	CustomLineEdit* registerNumber = new CustomLineEdit("Register Number", 100, 50, QString::number(static_cast<int>(configNonBase->registerNumber), 2), this, false);
	detailsLayout_->addWidget(registerNumber, 2, 4);
	detailsLayout_->addWidget(new CustomLineEdit("R", 100, 50, "", this), 2, 5);

	lineEditsMap["registerNumber"] = registerNumber;
}
void PacketDetails::viewConfigRead0() {
	createHeader();
	createConfigCommon();
	createCongigOHCvector();


}
void PacketDetails::viewConfigWrite0() {
	createHeader();
	createConfigCommon();
	createCongigOHCvector();
	createDataPayload(4);
}

void PacketDetails::updateView(TLP* tlp) {
	// Updates the view with the new TLP if the TLP is different from the current one
	//--------------------------------------------------commented till implementing equal in tlp-----------------------------------------------------------------
	/*if (tlp == currentTLP) {
		return;
	}*/
	clearView();
	currentTLP = tlp;
	lineEditsMap.clear();
	if(tlp->header->TLPtype == TLPType::MemRead32){
		viewMemRead32();
		contentLayout_->addLayout(detailsLayout_);

	}
	else if (tlp->header->TLPtype == TLPType::MemRead64) {
		viewMemRead64();
		contentLayout_->addLayout(detailsLayout_);
	}
	else if (tlp->header->TLPtype == TLPType::MemWrite32) {
		viewMemWrite32();
		contentLayout_->addLayout(detailsLayout_);

	}
	else if (tlp->header->TLPtype == TLPType::MemWrite64) {
		viewMemWrite64();
		contentLayout_->addLayout(detailsLayout_);

	}
	else if (tlp->header->TLPtype == TLPType::ConfigRead0 || tlp->header->TLPtype == TLPType::ConfigRead1) {
		viewConfigRead0();
		contentLayout_->addLayout(detailsLayout_);
	}
	else if (tlp->header->TLPtype == TLPType::ConfigWrite0 || tlp->header->TLPtype == TLPType::ConfigWrite1) {
		viewConfigWrite0();
		contentLayout_->addLayout(detailsLayout_);
	}
	else {
		//place holder
		QLabel* label = new QLabel(QString("TLPCard details"), this);
		//contentLayout_->addWidget(label);
		detailsLayout_->addWidget(label);
		contentLayout_->addLayout(detailsLayout_);
	}
	
}

void PacketDetails::clearView() {
	// Removes any existing content from the details view 
	
	QLayoutItem* child;
	while ((child = detailsLayout_->takeAt(0)) != nullptr) {
		if (child->widget() != saveButton) {

			delete child->widget();
			delete child;
		}
		
	}
	

	
}

void PacketDetails::saveMemCommon32() {
	AddressRouting32Bit* addressRouting = dynamic_cast<AddressRouting32Bit*>(currentTLP->header->nonBase);
	addressRouting->address = binaryToInteger(lineEditsMap["address"]->lineEdit->text().toStdString());


	OHCA1* ohca1 = dynamic_cast<OHCA1*>(currentTLP->header->OHCVector[0]);
	ohca1->firstDWBE = std::bitset<4>(lineEditsMap["firstDWBE"]->lineEdit->text().toStdString());
	ohca1->lastDWBE = std::bitset<4>(lineEditsMap["lastDWBE"]->lineEdit->text().toStdString());
}
void PacketDetails::saveMemCommon64() {
	AddressRouting64Bit* addressRouting = dynamic_cast<AddressRouting64Bit*>(currentTLP->header->nonBase);
	std::string upperAddress = lineEditsMap["upperAddress"]->lineEdit->text().toStdString();
	std::string lowerAddress = lineEditsMap["lowerAddress"]->lineEdit->text().toStdString();
	addressRouting->address = combineAddresses(upperAddress, lowerAddress);


	OHCA1* ohca1 = dynamic_cast<OHCA1*>(currentTLP->header->OHCVector[0]);
	ohca1->firstDWBE = std::bitset<4>(lineEditsMap["firstDWBE"]->lineEdit->text().toStdString());
	ohca1->lastDWBE = std::bitset<4>(lineEditsMap["lastDWBE"]->lineEdit->text().toStdString());
}
void PacketDetails::saveDataPayload() {
	currentTLP->dataPayload.clear();
	std::string dataString = lineEditsMap["dataPayload"]->lineEdit->text().toStdString();
	//append each bit to the data payload
	for (int i = dataString.size() - 1; i >= 0; i--) {
		currentTLP->dataPayload.push_back(dataString[i] - '0');
	}
	//adjust tlp length
	currentTLP->header->lengthInDoubleWord = ceil((float)currentTLP->dataPayload.size() / 32);
}

void PacketDetails::saveConfigCommon() {
	ConfigNonHeaderBase* configNonBase = dynamic_cast<ConfigNonHeaderBase*>(currentTLP->header->nonBase);
	configNonBase->registerNumber = binaryToInteger(lineEditsMap["registerNumber"]->lineEdit->text().toStdString());

	OHCA3* ohca3 = dynamic_cast<OHCA3*>(currentTLP->header->OHCVector[0]);
	ohca3->firstDWBE = std::bitset<4>(lineEditsMap["firstDWBE"]->lineEdit->text().toStdString());
	ohca3->lastDWBE = std::bitset<4>(lineEditsMap["lastDWBE"]->lineEdit->text().toStdString());
	ohca3->destinationSegment = binaryToInteger(lineEditsMap["destinationSegment"]->lineEdit->text().toStdString());
}


void PacketDetails::saveValues() {
	
	if (currentTLP->header->TLPtype == TLPType::MemRead32) {
		saveMemCommon32();
	}
	else if (currentTLP->header->TLPtype == TLPType::MemRead64) {
		saveMemCommon64();
	}
	else if (currentTLP->header->TLPtype == TLPType::MemWrite32) {
		saveMemCommon32();

		//saving data payload
		saveDataPayload();

	}
	else if (currentTLP->header->TLPtype == TLPType::MemWrite64) {
		saveMemCommon64();
		//saving data payload
		saveDataPayload();
	}
	else if (currentTLP->header->TLPtype == TLPType::ConfigRead0 || currentTLP->header->TLPtype == TLPType::ConfigRead1) {
		saveConfigCommon();
	}
	else if (currentTLP->header->TLPtype == TLPType::ConfigWrite0 || currentTLP->header->TLPtype == TLPType::ConfigWrite1) {
		saveConfigCommon();
		//saving data payload
		saveDataPayload();
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
	contentLayout_->addLayout(detailsLayout_);
	saveButton = new QPushButton("Save",this);

	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveValues()));

	//make the button at the bottom
	contentLayout_->addStretch();

	contentLayout_->addWidget(saveButton);
	setLayout(contentLayout_);

	
}