#include "DayzUtil.h";

bool DayZUtil::isPointerValid(QWORD ptr) {
	if (ptr > 0x200000001 && ptr < 0xffffffff00000000)
		return true;
	return false;
	// check alignment
	if (ptr % sizeof(void*) != 0) {
		return false; // not aligned
	}

}