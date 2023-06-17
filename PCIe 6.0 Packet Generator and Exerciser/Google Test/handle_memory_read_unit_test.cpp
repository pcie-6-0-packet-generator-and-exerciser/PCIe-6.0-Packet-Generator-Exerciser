#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/endpoint_app/endpoint_app.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/memory_mapper/memory_mapper.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/controller_class/memory_controller.h"

using namespace boost;


TEST(MemoryReadRequests, memoryReadRequest32) {

    // this constructor to initialize the memory map and memory controller with the memory map
    EndpointApp* endpointApp = new EndpointApp();
    MemoryController* memoryController = endpointApp->getMemoryController();
    memoryController->constructMemoryController();
    // construct the configuration controller and enabling the memoryenabled bit
    ConfigurationController* controller = endpointApp->getConfigurationController();
    controller->constructConfigurationController();
    controller->configuration->getHead()->getRegisterNext()->getRegisterNext()->setRegisterValue(2);

    // I want to create the queue and add a TLP to it before sending it to the receivePackets function
    std::queue<TLP*> receivedQueue;
    // constructing the TLP request
    TLP* tlpRequest = new TLP();

    // the createMemRead32TLP method takes int dataPayloadLengthInDW, int requesterId, int tag, int address, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE 
    TLP* request = tlpRequest->createMemRead32Tlp(1, 0, 0, 3 , std::bitset<4>(0b1111), std::bitset<4>(0b1111));

    // adding the TLP to the queue
    receivedQueue.push(request);
    // exception is thrown in case we are constructing UR request for any reason
    // calling the receivePackets function to receive the packet 
    endpointApp->receivePackets(receivedQueue);
    
    // after receiving the packet the endpoint should have a completion in the completion queue
    // so I will pop the completion queue and check if the completion is correct or not
    // this is the completion that should be in the completion queue
    TLP* completion = endpointApp->getCompletionQueue().front();

    // this is the exptected completion
    TLP* expectedCompletion = new TLP();
    int completerSegment = 0;
    int destinationSegment = 0;
    std::bitset<2> lowerAddressOHC = std::bitset<2>(0b00);
    std::bitset<5> lowerAddressHeaderBase = std::bitset<5>(0b00000);

    // createCplDTlp() takes as parameters: int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddressOHC, std::bitset<5> lowerAddressHeaderBase, OHCA5::CPLStatus cplStatus)
    expectedCompletion =  expectedCompletion->createCplDTlp(
        1, // dataPayloadLengthInDW
        boost::dynamic_bitset<>(32,0),// dataPayload
        0, // tag
        0, // completerId
        0, // byteCount
        0, // busNumber
        0, // deviceNumber
        0, // functionNumber
        destinationSegment, // destinationSegment
        completerSegment, // completerSegment
        lowerAddressOHC,
        lowerAddressHeaderBase,
        OHCA5::CPLStatus::True // cplStatus
    );

    // the completion should be a completion with data
    // I will compare the two completions
    // should compare each field in the completion with the expected completion
    EXPECT_EQ(completion->dataPayload, expectedCompletion->dataPayload);
}


/*TEST(MemoryReadRequests, memoryReadRequest64) {

    // this constructor to initialize the memory map and memory controller with the memory map
    EndpointApp* endpointApp = new EndpointApp();
    // I want to create the queue and add a TLP to it before sending it to the receivePackets function
    std::queue<TLP*> receivedQueue;
    // constructing the TLP request
    TLP* tlpRequest = new TLP();

    // the createMemRead64TLP method takes int dataPayloadLengthInDW, int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4> lastDWBE 
    TLP* request = tlpRequest->createMemRead64Tlp(3,  0, 0, 3, std::bitset<4>(0b1111), std::bitset<4>(0b1111));
    request->header->lengthInDoubleWord = 3;
    // adding the TLP to the queue
    receivedQueue.push(request);

    // calling the receivePackets function to receive the packet 
    endpointApp->receivePackets(receivedQueue);

    // after receiving the packet the endpoint should have a completion in the completion queue
    // so I will pop the completion queue and check if the completion is correct or not
    // this is the completion that should be in the completion queue
    std::queue<TLP*> completionQueue = endpointApp->getCompletionQueue();
    TLP* completion = completionQueue.front();

    // this is the exptected completion
    TLP* expectedCompletion = new TLP();
    int completerSegment = 0;
    int destinationSegment = 0;
    std::bitset<2> lowerAddressOHC = std::bitset<2>(0b00);
    std::bitset<5> lowerAddressHeaderBase = std::bitset<5>(0b00000);

    // createCplDTlp() takes as parameters: int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddressOHC, std::bitset<5> lowerAddressHeaderBase, OHCA5::CPLStatus cplStatus)
    expectedCompletion->createCplDTlp(
        3, // dataPayloadLengthInDW
        boost::dynamic_bitset<>(96, 0),//dataPayload
        0, // tag
        0, // completerId
        0, // byteCount
        0, // busNumber
        0, // deviceNumber
        0, // functionNumber
        destinationSegment, // destinationSegment
        completerSegment, // completerSegment
        lowerAddressOHC,
        lowerAddressHeaderBase,
        OHCA5::CPLStatus::True // cplStatus
    );

    // the completion should be a completion with data
    // I will compare the two completions
    EXPECT_EQ(completion->dataPayload, expectedCompletion->dataPayload);
}*/

