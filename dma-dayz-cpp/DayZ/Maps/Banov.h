#pragma once
#include "DMARender/includes.h"
namespace DayZ {
	class Banov : public DMARender::IGameMap {


	public:
		Banov() : DMARender::IGameMap(std::string("Banov"), std::string("maps\\banov.png")) {}

		// Inherited via IGameMap
		virtual ImVec2 translatePoint(const DMARender::Vector3& gamePoint) override;
	};
}