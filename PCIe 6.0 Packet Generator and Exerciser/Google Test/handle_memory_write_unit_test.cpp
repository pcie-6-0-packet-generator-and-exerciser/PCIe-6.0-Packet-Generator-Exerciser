#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/endpoint_app/endpoint_app.h"


TEST(MemoryWriteRequests, memoryWrite32Request){

	// want to test the memory write request
	// to test if the memory write request is working correctly
	// I will create a memory write request and send it to the endpoint
	// then I will check if the memory is written correctly or not
	// I will check the memory by reading from it and checking the value
	// I will use the memory mapper to read from the memory
	
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

    // int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4>lastDWBE
    boost::dynamic_bitset<> dataPayload(32, 0b11111111000000001111111100000000);
    TLP* request = tlpRequest->createMemWrite32Tlp(1, dataPayload, 0, 0, 3,  std::bitset<4>(0b1111), std::bitset<4>(0b1111));

    // adding the TLP to the queue
    receivedQueue.push(request);
    // exception is thrown in case we are constructing UR request for any reason
    // calling the receivePackets function to receive the packet
    endpointApp->receivePackets(receivedQueue);

    // after receiving the packet the endpoint should have written the data to the memory

    // now I will read from the memory and check if the data is written correctly or not

    // I will use the memory mapper to read from the memory
    MemoryMap* memoryMap = memoryController->getMemoryMap();
    // I will read from the memory address 3
    boost::dynamic_bitset<> data = memoryMap->read(3 , 1 , std::bitset<4>(0b1111), std::bitset<4>(0b1111));
    boost::dynamic_bitset<> expectedData(32, 0b11111111000000001111111100000000);

    EXPECT_EQ(data, expectedData);
}

