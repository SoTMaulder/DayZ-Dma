#pragma once
#include "DMARender/includes.h"
#include "../MemoryUpdater/MemoryUpdater.h"
#include <fstream> 
namespace DayZ {
	class OverlayAdapter : public DMARender::IOverlay {

		//DayZ::MemoryUpdater* memUpdater;


		std::shared_ptr<DayZ::MemoryUpdater> memUpdater; // Shared Pointer
		std::shared_ptr<DMARender::RenderBridge> renderBridge; // Shared Pointer
		//std::set<std::string> favoriteSteamIDs; // SteamIDs from textfile
		//void loadFavoriteSteamIDs(const std::string& filePath); // function to load SteamIDs from textfile


		bool WorldToScreenDayZ(DayZ::Camera* camera, const DMARender::Vector3& position, DMARender::Vector2& outVector);
		void drawLoot(DayZ::Camera* camera, const std::vector<std::shared_ptr<DayZ::Entity>>& entities);
		void drawAliveEntities(DayZ::Camera* camera, const std::vector<std::shared_ptr<DayZ::Entity>>& entities, Scoreboard* scoreboard);
		void drawDebugInformation(DayZ::Camera* camera, const std::vector<std::shared_ptr<DayZ::Entity>>& entities);



		//Fonts
		ImFont* lootFont;
		ImFont* lootFontFar;
		ImFont* playerFont;


	public:
		OverlayAdapter(std::shared_ptr<DayZ::MemoryUpdater> memUpdater, std::shared_ptr<DMARender::RenderBridge> renderBridge);
		// Inherited via IOverlay
		virtual void DrawOverlay() override;
		virtual void createFonts() override;
	};
}