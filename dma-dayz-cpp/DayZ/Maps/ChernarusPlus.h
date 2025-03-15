#pragma once
#include "DMARender/includes.h"
namespace DayZ {
	class ChernarusPlus : public DMARender::IGameMap {
		

	public:
		ChernarusPlus() : DMARender::IGameMap(std::string("Chernarus Plus"), std::string("maps\\chernarusplus.png")) {}

		// Inherited via IGameMap
		virtual ImVec2 translatePoint(const DMARender::Vector3& gamePoint) override;
	};
}