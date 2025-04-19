#include "./VmmManager.h"

VMM_HANDLE DMAMem::VmmManager::getVmm() {
	if (!hVMM) {
		hVMM = initialize();
	}
	return hVMM;
}


VMM_HANDLE DMAMem::VmmManager::initialize()
{
	VMMDLL_CloseAll();
	std::cout << " [ + ] Connecting to DMA Card..." << std::endl;

	LPSTR args[] = { LPSTR(""), LPSTR("-device"), LPSTR("fpga://algo=0") };

	VMM_HANDLE handle = VMMDLL_Initialize(3, args);
	if (!handle)
		std::cout << "[ ! ] Vmm Initialization Failed..." << std::endl;

	std::cout << " [ + ] Connected to DMA Card..." << std::endl;

	return handle;
}

BOOL DMAMem::VmmManager::readMemory(DWORD pid, QWORD remoteAddress, void* destination, int size, ULONG64 flags)
{
	return VMMDLL_MemReadEx(this->getVmm(), pid, remoteAddress, (PBYTE)destination, size, NULL, flags);
}

VMMDLL_SCATTER_HANDLE DMAMem::VmmManager::initializeScatter(DWORD pid)
{
	return initializeScatter(pid, VMMDLL_FLAG_NOCACHE);
}

VMMDLL_SCATTER_HANDLE DMAMem::VmmManager::initializeScatter(DWORD pid, ULONG64 flags)
{
	return VMMDLL_Scatter_Initialize(this->getVmm(), pid, flags);
}

void DMAMem::VmmManager::addScatterRead(VMMDLL_SCATTER_HANDLE handle, QWORD remoteAddress, int size, void* destination)
{
	VMMDLL_Scatter_PrepareEx(handle, remoteAddress, size, (PBYTE)destination, nullptr);
}

void DMAMem::VmmManager::executeScatter(VMMDLL_SCATTER_HANDLE handle)
{
	VMMDLL_Scatter_ExecuteRead(handle);
	VMMDLL_Scatter_CloseHandle(handle);
}
