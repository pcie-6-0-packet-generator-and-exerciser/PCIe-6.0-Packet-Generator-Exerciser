#pragma once
#include "../../utils/tlp.h"
#include "../controller_class/configuration_controller.h"
#include <queue>
#include "../controller_class/memory_controller.h"

class EndpointApp {
public:
	EndpointApp();
	void receivePackets(std::queue<TLP> receievedTLPs);
	void sendCompletions();
    void clearCompletionsQueue();

private:
    // Add BAR variables
    uint64_t prefetchableBar0_;
    uint32_t nonPrefetchableBar2_;
    uint16_t ioBar3_;
    std::unique_ptr<MemoryController> memoryController_;
    std::unique_ptr<ConfigurationController> configurationController_;
    std::unique_ptr<MemoryMap> memoryMap_;

    // Add queue wrapper for TLPs received from root complex
    QueueWrapper<TLP>* tlpQueueWrapper_;

    // Add queue wrapper for completions sent to root complex
    QueueWrapper<TLP>* completionQueueWrapper_;
};