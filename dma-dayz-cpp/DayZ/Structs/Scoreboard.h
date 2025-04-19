#pragma once
#include "DMAMemoryManagement/includes.h";
#include "ScoreboardIdentity.h";
#include <set>;
#include "../DayzUtil.h";

namespace DayZ {
	class Scoreboard : public DMAMem::MemoryObject {
		QWORD ScoreboardIdentityPointers[120];


	protected:
		std::vector<DMAMem::MemoryObject::ResolutionRequest> postResolveResolutions() override {
			if (resolvedIdentities.size() > 0) {
				std::vector<ResolutionRequest> requestVec;
				for (auto const ident : resolvedIdentities) {
					auto entRes = ident->getRequestedResolutions(ident->_remoteAddress);
					DMAUtils::concatVectors(&requestVec, &entRes);
				}
				return requestVec;
			}
			std::vector<ResolutionRequest> requestVec;
			std::set<QWORD> vecEntityPointers(std::begin(ScoreboardIdentityPointers), std::end(ScoreboardIdentityPointers));
			for (QWORD identityPtr : vecEntityPointers) {
				if (DayZUtil::isPointerValid(identityPtr)) {
					auto ent = std::shared_ptr<ScoreboardIdentity>(new ScoreboardIdentity());
					auto entRes = ent->getRequestedResolutions(identityPtr);
					DMAUtils::concatVectors(&requestVec, &entRes);
					resolvedIdentities.push_back(ent);
				}
			}
			return requestVec;
		}

	public:
		std::vector<std::shared_ptr<ScoreboardIdentity>> resolvedIdentities;
		Scoreboard() {
			this->registerOffset(0x0, &ScoreboardIdentityPointers, sizeof(QWORD[120]));
		}

	};
}


//
//#pragma once
//#include "DMAMemoryManagement/includes.h"
//#include "ScoreboardIdentity.h"
//#include <set>
//#include "../DayzUtil.h"
//
//namespace DayZ {
//    class Scoreboard : public DMAMem::MemoryObject {

//        std::vector<QWORD> ScoreboardIdentityPointers;
//        int tableSize;
//    protected:
//        std::vector<DMAMem::MemoryObject::ResolutionRequest> postResolveResolutions() override {
//            
//            std::vector<QWORD> currentValidPointers;
//            for (int i = 0; i < tableSize; ++i) {
//                QWORD ptr = ScoreboardIdentityPointers[i];
//                if (DayZUtil::isPointerValid(ptr))
//                    currentValidPointers.push_back(ptr);
//            }
//
//            // useCache
//            bool useCache = (!resolvedIdentities.empty() && (currentValidPointers.size() == resolvedIdentities.size()));
//            if (useCache) {
//                std::vector<ResolutionRequest> requestVec;
//                for (const auto& ident : resolvedIdentities) {
//                    auto identRes = ident->getRequestedResolutions(ident->_remoteAddress);
//                    DMAUtils::concatVectors(&requestVec, &identRes);
//                }
//                return requestVec;
//            }
//
//            // clear and rebuild
//            resolvedIdentities.clear();
//            std::vector<ResolutionRequest> requestVec;
//            for (int i = 0; i < tableSize; ++i) {
//                QWORD identityPtr = ScoreboardIdentityPointers[i];
//                if (!DayZUtil::isPointerValid(identityPtr))
//                    continue;
//                auto ident = std::make_shared<ScoreboardIdentity>();
//                auto identRes = ident->getRequestedResolutions(identityPtr);
//                DMAUtils::concatVectors(&requestVec, &identRes);
//                resolvedIdentities.push_back(ident);
//            }
//            return requestVec;
//        }
//    public:
//        std::vector<std::shared_ptr<ScoreboardIdentity>> resolvedIdentities;
//
//        // default constructor
//        Scoreboard() : Scoreboard(120) {}
//
//        // "tablesize" constructor
//        Scoreboard(int size) : tableSize(size), ScoreboardIdentityPointers(size, 0) {
//            this->registerOffset(0x0, ScoreboardIdentityPointers.data(), sizeof(QWORD) * tableSize);
//        }
//    };
//}
