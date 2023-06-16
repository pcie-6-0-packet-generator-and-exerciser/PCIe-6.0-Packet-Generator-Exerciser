#pragma once

#include <memory>
#include "../../utils/tlp.h"
#include "../endpoint_app/memory_request_handler.h"


/* Singleton class */
class MemoryController {

private:
    static MemoryController* memoryController;
    MemoryController(); // Making a private constructor to avoid the new operators
    MemoryMap* memoryMap_;
    std::shared_ptr<MemoryRequestHandler> handler;

public:
    static MemoryController* constructMemoryController();
    TLP* handleMemoryReadRequest(TLP* tlp);
    void handleMemoryWriteRequest(TLP* tlp);
};



