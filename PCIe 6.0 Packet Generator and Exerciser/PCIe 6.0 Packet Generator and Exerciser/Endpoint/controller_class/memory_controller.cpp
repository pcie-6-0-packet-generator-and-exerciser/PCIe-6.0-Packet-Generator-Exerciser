#include "memory_controller.h"
#include "../memory_mapper/memory_mapper.h"

MemoryController* MemoryController::memoryController = nullptr;

/**
 * @brief Construct a new Memory Controller object
 * * 
 * * @return MemoryController* 
 * */
MemoryController* MemoryController::constructMemoryController()
{
    if (memoryController == nullptr)
        memoryController = new MemoryController();

    return memoryController;
}

/**
 * @brief Construct a new Configuration Controller and initializing some needed pointers to be used inside it
 */
MemoryController::MemoryController()
{
    memoryMap_ = MemoryMap::constructMemoryMap();
    handler = make_shared<MemoryRequestHandler>(memoryMap_);
}


TLP* MemoryController::handleMemoryReadRequest(TLP* tlp) {

    if (tlp->header->TLPtype == TLPType::MemRead32 || tlp->header->TLPtype == TLPType::MemRead64) {

        return handler->handleMemoryRead(tlp, tlp->header->TLPtype);
    }
    else {
        // Handle unsupported TLP types
        return nullptr;
    }
}

void MemoryController::handleMemoryWriteRequest(TLP* tlp) {
    if (tlp->header->TLPtype == TLPType::MemWrite32 || tlp->header->TLPtype == TLPType::MemWrite64) {
		handler->handleMemoryWrite(tlp, tlp->header->TLPtype);
	}
    else {
		// Handle unsupported TLP types
	}
}


MemoryMap* MemoryController::getMemoryMap() {
	return memoryMap_;
}

