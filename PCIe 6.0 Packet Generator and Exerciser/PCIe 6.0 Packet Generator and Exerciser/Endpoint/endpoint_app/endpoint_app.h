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
    void run(QueueWrapper<TLP*>& sendOn, QueueWrapper<TLP*>& listenOn);
    std::queue<TLP*> getCompletionQueue();
    ConfigurationController* getConfigurationController();
    MemoryController* getMemoryController();

private:
    MemoryController*  memoryController_;
    ConfigurationController*  configurationController_;
    std::queue<TLP*> completionQueue_;
};