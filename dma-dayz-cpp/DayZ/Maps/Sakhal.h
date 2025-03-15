#pragma once
#include "DMARender/includes.h"
namespace DayZ {
	class Sakhal : public DMARender::IGameMap {


	public:
		Sakhal() : DMARender::IGameMap(std::string("Sakhal"), std::string("maps\\sakhal.png")) {}

		// Inherited via IGameMap
		virtual ImVec2 translatePoint(const DMARender::Vector3& gamePoint) override;
	};
}