#include "EndpointApp.h"

EndpointApp::EndpointApp(PCIeController* controller, MemoryMap* memoryMap, ConfigurationSpace* configSpace) :
    controller_(controller),
    memoryMap_(memoryMap),
    configSpace_(configSpace) {}

void EndpointApp::receiveTlpPacket(TlpPacket packet) {
    // implementation of receiveTlpPacket function
}

