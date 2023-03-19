#include "endpoint_app.h"

EndpointApp::EndpointApp()
    : prefetchableBar0_(0x100000000ull), // 1 GB prefetchable BAR 0
    nonPrefetchableBar2_(0x4000000),   // 64 MB non-prefetchable BAR 2
    ioBar3_(0x100)                     // I/O BAR 3
{
    memoryMap_ = std::make_unique<MemoryMap>(prefetchableBar0_, nonPrefetchableBar2_, ioBar3_);
    memoryController_ = std::make_unique<MemoryController>(std::make_unique<MemoryMap>(prefetchableBar0_, nonPrefetchableBar2_, ioBar3_));
    configurationController_ = ConfigurationController::constructConfigurationController();
}


void EndpointApp::receivePackets(std::queue<TLP> receivedQueue) {
    while (true) {
        if (receivedQueue.empty()) {
            break;
        }
        TLP packet = receivedQueue.front();
        receivedQueue.pop();
        TLP responseTlp;

        if (packet.header->TLPtype == TLPType::MemRead32 || packet.header->TLPtype == TLPType::MemRead64
            || packet.header->TLPtype == TLPType::MemWrite32 || packet.header->TLPtype == TLPType::MemWrite64) {
            responseTlp = memoryController_->handleTlp(packet);
            completionQueue_.push(responseTlp);
        }
        else if (packet.header->TLPtype == TLPType::ConfigRead0 || packet.header->TLPtype == TLPType::ConfigRead1
            || packet.header->TLPtype == TLPType::ConfigWrite0 || packet.header->TLPtype == TLPType::ConfigWrite1) {
            responseTlp = configurationController_->handleConfigurationRequest(&packet);
            completionQueue_.push(responseTlp);
        }
        else {
            auto cpl = std::make_unique<CompletionWithUR>();
            responseTlp = *cpl->constructTLP();
            completionQueue_.push(responseTlp);
        }
    }
}



void EndpointApp::sendCompletions() {
        // Send completions to root complex
}



void EndpointApp::clearCompletionsQueue() {
    completionQueue_ = std::queue<TLP>();
}

