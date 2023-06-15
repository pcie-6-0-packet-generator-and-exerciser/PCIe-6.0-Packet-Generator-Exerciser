#include "utils.h"

int getHeaderLengthByType(TLPType type) {
	switch (type) {
	case TLPType::MemRead32:
		return 12;
		break;
	case TLPType::MemWrite32:
		return 12;
		break;
	case TLPType::MemRead64:
		return 16;
		break;
	case TLPType::MemWrite64:
		return 16;
		break;
	case TLPType::Cpl:
		return 12;
		break;
	case TLPType::CplD:
		return 16;
		break;
	case TLPType::VendorMsg:
		return 12;
		break;
	case TLPType::ConfigRead0:
		return 12;
		break;
	case TLPType::ConfigWrite0:
		return 12;
		break;
	case TLPType::ConfigRead1:
		return 16;
		break;
	case TLPType::ConfigWrite1:
		return 16;
		break;
	default:
		break;
	}
}