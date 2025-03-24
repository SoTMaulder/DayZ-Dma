#pragma once
#include "DMARender/includes.h"
namespace DayZ {
	class Takistan : public DMARender::IGameMap {


	public:
		Takistan() : DMARender::IGameMap(std::string("Takistan"), std::string("maps\\takistan.png")) {}

		// Inherited via IGameMap
		virtual ImVec2 translatePoint(const DMARender::Vector3& gamePoint) override;
	};
}