#include "memory_write_handler.h"

/**
 * @brief 
 * @param packet 
*/

void MemoryWriteHandler::handleTlp(TLP packet) {
    // Verify that the TLP is a memory write TLP
    if (packet.header->TLPtype != TLPType::MemWrite32 && packet.header->TLPtype != TLPType::MemWrite64) {
        // If not, do nothing and return
        return;
    }

    // Extract the destination segment from the OHC vector in the TLP header
    int destinationSegment = 0;
    for (const auto& ohc : packet.header->OHCVector) {
        if (auto ohca4 = dynamic_cast<const OHCA4*>(&ohc)) {
            destinationSegment = ohca4->destinationSegment;
            break;
        }
    }
    // Write the data payload to the memory at the specified destination segment
    // (implementation of this step depends on the specific system and memory interface being used)
    //writeMemory(destinationSegment, packet.dataPayload);
}

