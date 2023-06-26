#include "packet_details_widget.h"
#include <unordered_map>


using namespace Ui;

PacketDetails::PacketDetails(QWidget* parent)
	: QFrame(parent)

{
	contentLayout_ = new QVBoxLayout;
	detailsLayout_ = new QGridLayout;
	detailsLayout_->setSpacing(0);
	detailsLayout_->setHorizontalSpacing(0);
	detailsLayout_->setVerticalSpacing(0);
	detailsLayout_->setContentsMargins(0, 0, 0, 0);
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
	
	CustomLineEdit* type = new CustomLineEdit("Type", 8*width, height, QString::number(static_cast<int>(currentTLP->header->TLPtype), 2).rightJustified(8, '0'), this);
	detailsLayout_->addWidget(type,0,0,1,8);
	CustomLineEdit* tc = new CustomLineEdit("TC", 3*width, height, "000", this);
	detailsLayout_->addWidget(tc,0,8,1,3);
	CustomLineEdit* ohc = new CustomLineEdit("OHC", 5*width, height, "00001", this);
	detailsLayout_->addWidget(ohc,0,11,1,5);
	CustomLineEdit* ts = new CustomLineEdit("TS", 3*width, height, "000", this);
	detailsLayout_->addWidget(ts,0,16,1,3);
	CustomLineEdit* attr = new CustomLineEdit("Attr", 3*width, height, "000", this);
	detailsLayout_->addWidget(attr,0,19,1,3);
	if(currentTLP->header->TLPtype == TLPType::MemRead32|| currentTLP->header->TLPtype == TLPType::MemRead64 ) {
		CustomLineEdit* length = new CustomLineEdit("Length", 10*width, height, QString::number(static_cast<int>(currentTLP->header->lengthInDoubleWord), 2).rightJustified(10, '0'), this, false);
		detailsLayout_->addWidget(length, 0, 22,1,10);
		lineEditsMap["length"] = length;
	}
	else{
		CustomLineEdit* length = new CustomLineEdit("Length", 10*width, height, QString::number(static_cast<int>(currentTLP->header->lengthInDoubleWord), 2).rightJustified(10, '0'), this);
		detailsLayout_->addWidget(length, 0, 22,1,10);
	}
	
}
void PacketDetails::createMem32bCommon() {
	//creates the second dw in memory requests 32bit
	
	CustomLineEdit* requesterId = new CustomLineEdit("Requester ID", 16*width, height, "0000000000000", this);
	detailsLayout_->addWidget(requesterId, 1,0,1,16);
	CustomLineEdit* ep = new CustomLineEdit("EP", 1.5*width, height, "0", this);
	detailsLayout_->addWidget(ep,1,16,1,1);
	CustomLineEdit* reserved = new CustomLineEdit("R", 1.5*width, height, "", this);
	detailsLayout_->addWidget(reserved,1,17,1,1);
	NonHeaderBase* nonbase = currentTLP->header->nonBase;
	AddressRouting32Bit* addressRouting = dynamic_cast<AddressRouting32Bit*>(nonbase);
	CustomLineEdit* tag = new CustomLineEdit("Tag", 14*width, height, QString::number(static_cast<int>(addressRouting->tag), 2).rightJustified(14, '0'), this);
	detailsLayout_->addWidget(tag,1,18,1,14);

	//address
	CustomLineEdit* address = new CustomLineEdit("Address", 30*width, height, QString::number(static_cast<int>(addressRouting->address), 2).rightJustified(30, '0'), this, false);
	detailsLayout_->addWidget(address,2,0,1,30);
	CustomLineEdit* at = new CustomLineEdit("AT", 2*width, height, "00", this);
	detailsLayout_->addWidget(at,2,30,1,2);

	//saving to CurrentLineEdits
	lineEditsMap["address"] = address;
	

	

}

void PacketDetails::createMem64bCommon() {
	//creates the second dw in memory requests 64bit

	CustomLineEdit* requesterId = new CustomLineEdit("Requester ID", 16 * width, height, "0000000000000", this);
	detailsLayout_->addWidget(requesterId, 1, 0, 1, 16);
	CustomLineEdit* ep = new CustomLineEdit("EP", 1.5*width, height, "0", this);
	detailsLayout_->addWidget(ep, 1, 16, 1, 1);
	CustomLineEdit* reserved = new CustomLineEdit("R", 1.5*width, height, "", this);
	detailsLayout_->addWidget(reserved, 1, 17, 1, 1);
	NonHeaderBase* nonbase = currentTLP->header->nonBase;
	AddressRouting64Bit* addressRouting = dynamic_cast<AddressRouting64Bit*>(nonbase);
	CustomLineEdit* tag = new CustomLineEdit("Tag", 14 * width, height, QString::number(static_cast<int>(addressRouting->tag), 2).rightJustified(14, '0'), this);
	detailsLayout_->addWidget(tag, 1, 18, 1, 14);

	//address
	int upperAddressValue = (int)(addressRouting->address >> 32);
	CustomLineEdit* upperAddress = new CustomLineEdit("Address[63:32]", 32*width, height, QString::number(static_cast<int>(upperAddressValue), 2).rightJustified(32, '0'), this, false);
	detailsLayout_->addWidget(upperAddress, 2, 0,1,32);
	int lowerAddressValue = (int)addressRouting->address & 0xFFFFFFFF;
	CustomLineEdit* lowerAddress = new CustomLineEdit("Address[31:2]", 30*width, height, QString::number(static_cast<long long>(lowerAddressValue), 2).rightJustified(30, '0'), this,false);
	detailsLayout_->addWidget(lowerAddress, 3, 0,1,30);
	CustomLineEdit* at = new CustomLineEdit("AT", 2*width, height, "00", this);
	detailsLayout_->addWidget(at, 3, 30,1,2);

	//saving to address CurrentLineEdits
	lineEditsMap["upperAddress"] = upperAddress;
	lineEditsMap["lowerAddress"] = lowerAddress;


}
void PacketDetails::createConfigOHCvector() {
	//OHC
	OHC* ohcElement = currentTLP->header->OHCVector[0];
	OHCA3* ohca3 = dynamic_cast<OHCA3*>(ohcElement);
	CustomLineEdit* destination = new CustomLineEdit("Destination Segment", 8*width, height, QString::number(ohca3->destinationSegment,2).rightJustified(8,'0'), this);
	detailsLayout_->addWidget(destination,3, 0,1,8);
	

	detailsLayout_->addWidget(new CustomLineEdit("R", 8*width, height, "", this), 3, 8,1,8);
	detailsLayout_->addWidget(new CustomLineEdit("DSV", 1.5*width, height, "0", this), 3, 16,1,1);
	detailsLayout_->addWidget(new CustomLineEdit("R", 7*width, height, "", this), 3, 17,1,7);
	
	CustomLineEdit* firstDWBE = new CustomLineEdit("First DW BE", 4*width, height, QString::fromStdString(ohca3->firstDWBE.to_string()), this, false);
	detailsLayout_->addWidget(firstDWBE, 3, 24,1,4);
	CustomLineEdit* lastDWBE = new CustomLineEdit("Last DW BE", 4*width, height, QString::fromStdString(ohca3->lastDWBE.to_string()), this, false);
	detailsLayout_->addWidget(lastDWBE, 3, 28,1,4);


	//saving to currentLineEdits
	lineEditsMap["destinationSegment"] = destination;
	lineEditsMap["firstDWBE"] = firstDWBE;
	lineEditsMap["lastDWBE"] = lastDWBE;
}


void PacketDetails::createMemOHCvector(int row) {
	//OHC
	CustomLineEdit* nw = new CustomLineEdit("NW", 1.5*width, height, "0", this);
	detailsLayout_->addWidget(nw,row,0,1,1);
	CustomLineEdit* pv = new CustomLineEdit("PV", 1.5*width, height, "0", this);
	detailsLayout_->addWidget(pv,row,1,1,1);
	CustomLineEdit* pmr = new CustomLineEdit("PMR", 1.75*width, height, "0", this);
	detailsLayout_->addWidget(pmr,row,2,1,1);
	CustomLineEdit* pasid = new CustomLineEdit("PASID", 20*width, height, "0000000000000000000", this);
	detailsLayout_->addWidget(pasid,row,3,1,20);

	OHC* ohcElement = currentTLP->header->OHCVector[0];
	OHCA1* ohca1 = dynamic_cast<OHCA1*>(ohcElement);
	CustomLineEdit* firstDWBE = new CustomLineEdit("First DW BE", 4*width, height, QString::fromStdString(ohca1->firstDWBE.to_string()), this, false);
	detailsLayout_->addWidget(firstDWBE,row,24,1,4);
	CustomLineEdit* lastDWBE = new CustomLineEdit("Last DW BE", 4* width, height, QString::fromStdString(ohca1->lastDWBE.to_string()), this, false);
	detailsLayout_->addWidget(lastDWBE,row,28,1,4);


	//saving to currentLineEdits
	lineEditsMap["firstDWBE"] = firstDWBE;
	lineEditsMap["lastDWBE"] = lastDWBE;


}


void PacketDetails::createDataPayload(int row, bool readOnly) {
	
	
	string dataString;
	boost::to_string(currentTLP->dataPayload, dataString);
	CustomLineEdit* data = new CustomLineEdit("Data", 32*width, 2*height, QString::fromStdString(dataString), this, readOnly);
	data->setScrollBarEnabled(true);
	detailsLayout_->addWidget(data,row,0,2,32);

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
void PacketDetails::viewCpl() {
	createHeader();
	createCplCommon();
}
void PacketDetails::viewCpld() {
	createHeader();
	createCplCommon();
	createDataPayload(4, true);
}
void PacketDetails::createCplCommon(){

	NonHeaderBase* nonbase = currentTLP->header->nonBase;
	CompletionNonHeaderBase* cplNonBase = dynamic_cast<CompletionNonHeaderBase*>(nonbase);

	CustomLineEdit* completerId = new CustomLineEdit("Completer ID", 16*width, height, QString::number(cplNonBase->completerID), this);
	detailsLayout_->addWidget(completerId, 1, 0,1,16);
	detailsLayout_->addWidget(new CustomLineEdit("EP", 1.5*width, height, "0", this), 1, 16,1,1);

	
	string laString;
	int n = static_cast<int>(cplNonBase->lowerAddress);
	for (int i = 0; n > 0; i++)
	{
		laString.push_back(( n % 2) + '0'); ;
		n = n / 2;
	}
	for (int i = 0; i < 5; i++)
	{
		laString.push_back('0');
	}
	
	CustomLineEdit* LA6 = new CustomLineEdit("LA[6]",1.5* width, height, QString::fromStdString(laString.substr(4,1)), this);
	detailsLayout_->addWidget(LA6, 1, 17,1,1);
	CustomLineEdit* tag = new CustomLineEdit("Tag[13:0]", 14*width, height, QString::number(static_cast<int>(cplNonBase->tag), 2).rightJustified(14,'0'), this);
	detailsLayout_->addWidget(tag, 1, 18,1,14);

	//bdf and byte count

	CustomLineEdit* busNumber = new CustomLineEdit("Bus Number", 8*width, height, QString::number(static_cast<int>(cplNonBase->busNumber), 2).rightJustified(8,'0'), this);
	detailsLayout_->addWidget(busNumber, 2, 0,1,8);
	CustomLineEdit* deviceNumber = new CustomLineEdit("Device Number", 5*width, height, QString::number(static_cast<int>(cplNonBase->deviceNumber), 2).rightJustified(5,'0'), this);
	detailsLayout_->addWidget(deviceNumber, 2, 8,1,5);
	CustomLineEdit* functionNumber = new CustomLineEdit("Function Number", 3*width, height, QString::number(static_cast<int>(cplNonBase->functionNumber), 2).rightJustified(3,'0'), this);
	detailsLayout_->addWidget(functionNumber, 2, 13,1,3);
	CustomLineEdit* LA5_2 = new CustomLineEdit("LA[5:2]", 4*width, height, QString::fromStdString(laString.substr(0, 4)), this);  
	detailsLayout_->addWidget(LA5_2, 2, 16,1,4);
	CustomLineEdit* byteCount = new CustomLineEdit("Byte Count", 12*width, height, QString::number(static_cast<int>(cplNonBase->byteCount), 2).rightJustified(12,'0'), this);
	detailsLayout_->addWidget(byteCount, 2, 20,1,12);


	//OHC A5
	OHC* ohcElement = currentTLP->header->OHCVector[0];
	OHCA5* ohca5 = dynamic_cast<OHCA5*>(ohcElement);
	CustomLineEdit* destination = new CustomLineEdit("Destination Segment", 8*width, height, QString::number(ohca5->destinationSegment, 2).rightJustified(8,'0'), this);
	detailsLayout_->addWidget(destination, 3, 0, 1,8);
	CustomLineEdit* completerSegment = new CustomLineEdit("Completer Segment", 8*width, height, QString::number(ohca5->completerSegment, 2).rightJustified(8, '0'), this);
	detailsLayout_->addWidget(completerSegment, 3, 8,1,8);
	detailsLayout_->addWidget(new CustomLineEdit("DSV", 1.5*width, height, "0", this) , 3, 16,1,1);
	detailsLayout_->addWidget(new CustomLineEdit("Reserved", 10*width, height, "", this), 3, 17,1,10);
    CustomLineEdit* LA4_0 = new CustomLineEdit("LA[1:0]", 2*width, height, QString::fromStdString(ohca5->lowerAddress.to_string()), this);  
	detailsLayout_->addWidget(LA4_0, 3, 27,1,2);
	CustomLineEdit* cplStatus = new CustomLineEdit("Cpl Status",3* width, height, QString::number(static_cast<int>(ohca5->CPLStatusEnum), 2).rightJustified(3,'0'), this);
	detailsLayout_->addWidget(cplStatus, 3, 29,1,3);

}
void PacketDetails::createConfigCommon() {
	CustomLineEdit* requesterId = new CustomLineEdit("Requester ID", 16*width, height, "000000000000000", this);
	detailsLayout_->addWidget(requesterId, 1, 0,1,16);
	CustomLineEdit* ep = new CustomLineEdit("EP", 1.5*width, height, "0", this);
	detailsLayout_->addWidget(ep, 1, 16,1,1);
	
	detailsLayout_->addWidget(new CustomLineEdit("R", 1.5*width, height, "", this), 1, 17,1,1);
	NonHeaderBase* nonbase = currentTLP->header->nonBase;
	ConfigNonHeaderBase* configNonBase = dynamic_cast<ConfigNonHeaderBase*>(nonbase);
	CustomLineEdit* tag = new CustomLineEdit("Tag", 14*width, height, QString::number(static_cast<int>(configNonBase->tag), 2).rightJustified(14,'0'), this);
	detailsLayout_->addWidget(tag, 1, 18,1,14);

	//bdf and register
	CustomLineEdit* busNumber = new CustomLineEdit("Bus Number", 8 * width, height, QString::number(static_cast<int>(configNonBase->busNumber), 2).rightJustified(8, '0'), this);
	detailsLayout_->addWidget(busNumber, 2, 0, 1, 8);
	CustomLineEdit* deviceNumber = new CustomLineEdit("Device Number", 5 * width, height, QString::number(static_cast<int>(configNonBase->deviceNumber), 2).rightJustified(5, '0'), this);
	detailsLayout_->addWidget(deviceNumber, 2, 8, 1, 5);
	CustomLineEdit* functionNumber = new CustomLineEdit("Function Number", 3 * width, height, QString::number(static_cast<int>(configNonBase->functionNumber), 2).rightJustified(3, '0'), this);
	detailsLayout_->addWidget(functionNumber, 2, 13, 1, 3);
	
	detailsLayout_->addWidget(new CustomLineEdit("R", 4*width, height, "", this), 2, 16,1,4);
	CustomLineEdit* registerNumber = new CustomLineEdit("Register Number",10* width, height, QString::number(static_cast<int>(configNonBase->registerNumber), 2).rightJustified(10,'0'), this, false);
	detailsLayout_->addWidget(registerNumber, 2, 20,1,10);
	detailsLayout_->addWidget(new CustomLineEdit("R", 2*width, height, "", this), 2, 30,1,2);

	lineEditsMap["registerNumber"] = registerNumber;
}
void PacketDetails::viewConfigRead() {
	createHeader();
	createConfigCommon();
	createConfigOHCvector();


}
void PacketDetails::viewConfigWrite() {
	createHeader();
	createConfigCommon();
	createConfigOHCvector();
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
		viewConfigRead();
		contentLayout_->addLayout(detailsLayout_);
	}
	else if (tlp->header->TLPtype == TLPType::ConfigWrite0 || tlp->header->TLPtype == TLPType::ConfigWrite1) {
		viewConfigWrite();
		contentLayout_->addLayout(detailsLayout_);
	}
	else if(tlp->header->TLPtype == TLPType::Cpl) {
		viewCpl();
		contentLayout_->addLayout(detailsLayout_);
	}
	else if (tlp->header->TLPtype == TLPType::CplD) {
		viewCpld();
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
	addressRouting->address = binaryToInteger(lineEditsMap["address"]->lineEdit->toPlainText().toStdString());


	OHCA1* ohca1 = dynamic_cast<OHCA1*>(currentTLP->header->OHCVector[0]);
	ohca1->firstDWBE = std::bitset<4>(lineEditsMap["firstDWBE"]->lineEdit->toPlainText().toStdString());
	ohca1->lastDWBE = std::bitset<4>(lineEditsMap["lastDWBE"]->lineEdit->toPlainText().toStdString());
}
void PacketDetails::saveMemCommon64() {
	AddressRouting64Bit* addressRouting = dynamic_cast<AddressRouting64Bit*>(currentTLP->header->nonBase);
	std::string upperAddress = lineEditsMap["upperAddress"]->lineEdit->toPlainText().toStdString();
	std::string lowerAddress = lineEditsMap["lowerAddress"]->lineEdit->toPlainText().toStdString();
	addressRouting->address = combineAddresses(upperAddress, lowerAddress);


	OHCA1* ohca1 = dynamic_cast<OHCA1*>(currentTLP->header->OHCVector[0]);
	ohca1->firstDWBE = std::bitset<4>(lineEditsMap["firstDWBE"]->lineEdit->toPlainText().toStdString());
	ohca1->lastDWBE = std::bitset<4>(lineEditsMap["lastDWBE"]->lineEdit->toPlainText().toStdString());
}
void PacketDetails::saveDataPayload() {
	currentTLP->dataPayload.clear();
	std::string dataString = lineEditsMap["dataPayload"]->lineEdit->toPlainText().toStdString();
	//append each bit to the data payload
	for (int i = dataString.size() - 1; i >= 0; i--) {
		currentTLP->dataPayload.push_back(dataString[i] - '0');
	}
	//adjust tlp length
	currentTLP->header->lengthInDoubleWord = ceil((float)currentTLP->dataPayload.size() / 32);
	int i = currentTLP->header->lengthInDoubleWord * 32 - dataString.size();
	for ( i ; i >0 ; i--) {
		currentTLP->dataPayload.push_back(0);
	}
	
}

void PacketDetails::saveConfigCommon() {
	ConfigNonHeaderBase* configNonBase = dynamic_cast<ConfigNonHeaderBase*>(currentTLP->header->nonBase);
	configNonBase->registerNumber = binaryToInteger(lineEditsMap["registerNumber"]->lineEdit->toPlainText().toStdString());
	
	OHCA3* ohca3 = dynamic_cast<OHCA3*>(currentTLP->header->OHCVector[0]);
	ohca3->firstDWBE = std::bitset<4>(lineEditsMap["firstDWBE"]->lineEdit->toPlainText().toStdString());
	ohca3->lastDWBE = std::bitset<4>(lineEditsMap["lastDWBE"]->lineEdit->toPlainText().toStdString());
	//ohca3->destinationSegment = binaryToInteger(lineEditsMap["destinationSegment"]->lineEdit->toPlainText().toStdString());
}

void PacketDetails::saveLengthMemRead() {
	//adjust tlp length
	currentTLP->header->lengthInDoubleWord = binaryToInteger(lineEditsMap["length"]->lineEdit->toPlainText().toStdString());;
}


void PacketDetails::saveValues() {
	
	if (currentTLP->header->TLPtype == TLPType::MemRead32) {
		saveLengthMemRead();
		saveMemCommon32();
	}
	else if (currentTLP->header->TLPtype == TLPType::MemRead64) {
		saveLengthMemRead();
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