#pragma once
#include "../../utils/tlp.h"
#include "../controller_class/configuration_controller.h"
#include "../controller_class/memory_controller.h"
#include "../memory_mapper/memory_mapper.h"
#include "../../utils/queue_wrapper.h"

class EndpointApp {
public:
	EndpointApp();
	void receivePackets(std::queue<TLP*> receievedTLPs);
	std::queue<TLP*> sendCompletions();
    void clearCompletionsQueue();
    void run(QueueWrapper<TLP*> sendOn, QueueWrapper<TLP*> listenOn);

private:
    // Add BAR variables
    uint64_t prefetchableBar0_;
    uint32_t nonPrefetchableBar2_;
    uint16_t ioBar3_;
    std::unique_ptr<MemoryController> memoryController_;
    ConfigurationController*  configurationController_;
    std::unique_ptr<MemoryMap> memoryMap_;

    // Add queue wrapper for completions sent to root complex
    std::queue<TLP*> completionQueue_;
};