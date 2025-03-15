#include "MemoryObject.h"

void DMAMem::MemoryObject::registerOffset(int offset, void* destination, int typeSize)
{
	OffsetEntry oe = OffsetEntry();
	oe.offset = offset;
	oe.destination = destination;
	oe.typeSize = typeSize;
	offsetVector.push_back(oe);
	_isBaseResolved = false;
}

void DMAMem::MemoryObject::registerPointer(int offset, MemoryObject* destination)
{
	std::shared_ptr<OffsetPointer> op(new OffsetPointer());
	op->offset = offset;
	op->destination = destination;
	op->resolvedAddress = NULL;
	pointerVector.push_back(op);
	_isBaseResolved = false;
}

std::vector<DMAMem::MemoryObject::ResolutionRequest> DMAMem::MemoryObject::getRequestedResolutions(QWORD baseAddress)
{
	std::vector<ResolutionRequest> requestVec;
	if (baseAddress == NULL)
		return requestVec;
	_remoteAddress = baseAddress;
	//Resolve Base
	if (!_isBaseResolved) {
		for (const auto offEntry : offsetVector) {
			ResolutionRequest resReq;
			resReq.address = baseAddress + offEntry.offset;
			resReq.destination = offEntry.destination;
			resReq.size = offEntry.typeSize;
			requestVec.push_back(resReq);
		}
		for (const auto ptrEntry : pointerVector) {
			ResolutionRequest resReq;
			resReq.address = baseAddress + ptrEntry->offset;
			resReq.destination = &ptrEntry->resolvedAddress;
			resReq.size = GAME_POINTER_SIZE;
			requestVec.push_back(resReq);
		}
		_isBaseResolved = true;
		return requestVec;
	}
	return postResolveResolutions();
}

void DMAMem::MemoryObject::readResolutions(VmmManager* manager, DWORD pid, std::vector<ResolutionRequest> resolutionRequests, ULONG64 flags)
{
	VMMDLL_SCATTER_HANDLE scatterHandle = manager->initializeScatter(pid, flags);
	for (const auto res : resolutionRequests) {
		manager->addScatterRead(scatterHandle, res.address, res.size, res.destination);
	}
	manager->executeScatter(scatterHandle);
}

std::vector<DMAMem::MemoryObject::ResolutionRequest> DMAMem::MemoryObject::getPointerResolutions()
{
	std::vector<ResolutionRequest> requestVec;
	for (const auto ptrEntry : pointerVector) {
		auto ptrResolutions = ptrEntry->destination->getRequestedResolutions(ptrEntry->resolvedAddress);
		if (ptrResolutions.size() > 0) {
			DMAUtils::concatVectors<ResolutionRequest>(&requestVec, &ptrResolutions);
		}
	}
	return requestVec;
}

std::vector<DMAMem::MemoryObject::ResolutionRequest> DMAMem::MemoryObject::postResolveResolutions()
{
	return getPointerResolutions();
}


void DMAMem::MemoryObject::resolveObject(VmmManager* manager, DWORD pid, QWORD address, ULONG64 flags)
{
	auto resolutions = this->getRequestedResolutions(address);
	while (resolutions.size() > 0) {
		readResolutions(manager, pid, resolutions, flags);
		resolutions = this->getRequestedResolutions(address);
	}
}
