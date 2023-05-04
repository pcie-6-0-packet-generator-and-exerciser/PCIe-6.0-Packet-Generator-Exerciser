#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/memory_mapper/memory_mapper.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/controller_class/memory_controller.h"


// todo: Handle Memory Read Scenario: 
// 1. Constructing the Memory Map
// 2. Constructing the Memory Controller
// 3. Constructing the TLP Request
// 4. Constructing the TLP Response
// 5. Comparing the TLP Response with the expected TLP Response


// this test goal is to check that the memory mapper is working correctly
TEST(MemoryReadRequests, checkMemoryMapper) {

	 // Constructing the memory map
	MemoryMap* memoryMap = new MemoryMap(0x100000000ull, 0x4000000, 0x100);

	// writing data to memory
	bool isDone = memoryMap->write(0x100000000ull, 0x12345678);

	// read data from memory
	uint32_t data1;
	memoryMap->read(0x100000000ull, &data1);
	EXPECT_EQ(data1, 0x12345678 );

}