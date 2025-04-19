#include "OverlayAdapter.h"
#include <imgui.h> 
#include <unordered_set>

// Constructor
DayZ::OverlayAdapter::OverlayAdapter(std::shared_ptr<DayZ::MemoryUpdater> memUpdater, std::shared_ptr<DMARender::RenderBridge> renderBridge)
	: memUpdater(memUpdater), renderBridge(renderBridge) {

	//loadFavoriteSteamIDs("steamids.txt"); // Read "steamids.txt" for your favorite admins
	//DayZ::Entity::initializeRareItems("rareitems.txt"); // Read "rareitems.txt" for rare itemlist, use TypeName e.g. CarBattery
}


void DayZ::OverlayAdapter::drawLoot(DayZ::Camera* camera, const std::vector<std::shared_ptr<DayZ::Entity>>& entities) {


	if (!renderBridge) return; // If the render bridge is not initialized, return

	bool showVehicles = renderBridge->shouldShowVehiclesFUSER();
	bool showBoats = renderBridge->shouldShowBoatsFUSER();
	bool showGrounditems = renderBridge->shouldShowGrounditemsFUSER();
	bool showDeadAnimals = renderBridge->shouldShowDeadAnimalsFUSER();
	bool showDeadPlayers = renderBridge->shouldShowDeadPlayersFUSER();
	bool showWeapons = renderBridge->shouldShowWeaponsFUSER();
	bool showClothing = renderBridge->shouldShowClothingFUSER();
	bool showBackpacks = renderBridge->shouldShowBackpacksFUSER();
	bool showProxyMagazines = renderBridge->shouldShowProxyMagazinesFUSER();
	bool showFood = renderBridge->shouldShowFoodFUSER();
	bool showAmmo = renderBridge->shouldShowAmmoFUSER();
	bool showRare = renderBridge->shouldShowRareFUSER();
	int showLootDistance = renderBridge->shouldlootDistanceFUSER();
	bool showOptics = renderBridge->shouldShowOpticsFUSER();
	bool showBase = renderBridge->shouldShowBaseFUSER();
	bool showMelee = renderBridge->shouldShowMeleeFUSER();
	bool showExplosives = renderBridge->shouldShowExplosivesFUSER();



	for (auto const item : entities) {

		if (!item->isValid())
			continue;

		float maxDist = 5000;
		std::string postFix = "";
		ImU32 textCol;

		float dist = camera->InvertedViewTranslation.Dist(item->FutureVisualStatePtr->position);

		// Color for items and dead stuff
		if (item->isPlayer() && item->isDead && showDeadPlayers) {
			textCol = IM_COL32(0, 255, 255, 255);
			postFix = " (Dead)";
		} else if (item->isAnimal() && item->isDead && showDeadAnimals) {
			textCol = IM_COL32(0, 255, 0, 255);
			postFix = " (Dead)";
		} else if (item->isCar() && showVehicles) {
			textCol = IM_COL32(255, 0, 245, 255);
		} else if (item->isBoat() && showBoats) {
			textCol = IM_COL32(255, 0, 245, 255);
		} else if (item->isRare() && showRare) {
			textCol = IM_COL32(255, 0, 255, 255);
		} else if (item->isBackpack() && showBackpacks) {
			textCol = IM_COL32(175, 255, 0, 255);
		} else if (item->isClothing() && showClothing) {
			textCol = IM_COL32(255, 255, 0, 255);
		} else if (item->isWeapon() && showWeapons) {
			textCol = IM_COL32(255, 0, 100, 255);
		} else if (item->isProxyMagazines() && showProxyMagazines) {
			textCol = IM_COL32(255, 117, 50, 255);
		} else if (item->isFood() && showFood) {
			textCol = IM_COL32(50, 140, 50, 255);
		} else if (item->isAmmo() && showAmmo) {
			textCol = IM_COL32(255, 117, 50, 255);
		} else if (item->isGroundItem() && showGrounditems) {
			textCol = IM_COL32(255, 255, 255, 255);
		} else if (item->isOptic() && showOptics) {
			textCol = IM_COL32(0, 150, 255, 255);
		} else if (item->isBase() && showBase) {
			textCol = IM_COL32(0, 150, 255, 255);
		} else if (item->isMelee() && showMelee) {
			textCol = IM_COL32(0, 150, 255, 255);
		} else if (item->isExplosives() && showExplosives) {
			textCol = IM_COL32(255, 0, 50, 255);
		}
		
		else
		{
			continue;
		}

		auto itemPos = item->FutureVisualStatePtr->position;
		auto screenPos = DMARender::Vector2();

		if (!WorldToScreenDayZ(camera, itemPos, screenPos))
			continue;

		if (dist > maxDist)
			continue;
		if (dist > showLootDistance && !item->isCar() && !item->isBoat())
			continue;
		if (dist > 50) {
			ImGui::PushFont(lootFontFar);
		}
		else {
			ImGui::PushFont(lootFont);
		}
		drawText(item->EntityTypePtr->getBestString()->value + postFix + " " + std::to_string(std::lround(dist)) + "m", screenPos, ImGui::GetFontSize(), textCol);
		ImGui::PopFont();

	}
}

bool DayZ::OverlayAdapter::WorldToScreenDayZ(DayZ::Camera* camera, const DMARender::Vector3& position, DMARender::Vector2& outVector)
{
	if (!camera) return false;


	DMARender::Vector3 temp = DMARender::Vector3(
		position.x - camera->InvertedViewTranslation.x,
		position.y - camera->InvertedViewTranslation.y,
		position.z - camera->InvertedViewTranslation.z
	);

	float x = temp.Dot(camera->InvertedViewRight);
	float y = temp.Dot(camera->InvertedViewUp);
	float z = temp.Dot(camera->InvertedViewForward);

	if (z < 0.65f) return false;


	ImVec2 windowSize = ImGui::GetWindowSize();


	float normalizedX = (x / camera->GetProjectionD1.x) / z;
	float normalizedY = (y / camera->GetProjectionD2.y) / z;


	outVector.x = (windowSize.x / 2) + (normalizedX * (windowSize.x / 2));
	outVector.y = (windowSize.y / 2) - (normalizedY * (windowSize.y / 2));
	return true;
}

//DayZ::OverlayAdapter::OverlayAdapter(DayZ::MemoryUpdater* memUpdater, std::shared_ptr<DMARender::RenderBridge> renderBridge)
//{
//	this->memUpdater = memUpdater;
//}

void DayZ::OverlayAdapter::DrawOverlay()
{
	auto camera = memUpdater->getCamera();
	auto itemTable = memUpdater->getItemTable();
	auto slowTable = memUpdater->getSlowEntityTable();
	auto nearTable = memUpdater->getNearEntityTable();
	auto farTable = memUpdater->getFarEntityTable();
	auto scoreboard = memUpdater->getScoreboard();
	drawLoot(camera.get(), itemTable->resolvedEntities);
	drawLoot(camera.get(), slowTable->resolvedEntities);
	drawLoot(camera.get(), nearTable->resolvedEntities);
	drawLoot(camera.get(), farTable->resolvedEntities);
	drawAliveEntities(camera.get(), nearTable->resolvedEntities, scoreboard.get());
	drawAliveEntities(camera.get(), farTable->resolvedEntities, scoreboard.get());


	bool showDebug = renderBridge->shouldShowDebugFUSER();
	if (showDebug) {
		drawDebugInformation(camera.get(), slowTable->resolvedEntities);
		drawDebugInformation(camera.get(), itemTable->resolvedEntities); // show items only
		drawDebugInformation(camera.get(), nearTable->resolvedEntities); // picks up buggy items
		drawDebugInformation(camera.get(), farTable->resolvedEntities);
	}



}

void DayZ::OverlayAdapter::createFonts()
{
	ImFontConfig config;
	config.OversampleH = 3;
	config.OversampleV = 1;
	config.GlyphExtraSpacing.x = 1.0f;
	lootFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16, &config);
	lootFontFar = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14, &config);
	playerFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14, &config);
}

void DayZ::OverlayAdapter::drawAliveEntities(DayZ::Camera* camera, const std::vector<std::shared_ptr<DayZ::Entity>>& entities, DayZ::Scoreboard* scoreboard)
{

	if (!renderBridge) return; // If the render bridge is not initialized, return

	bool showZombies = renderBridge->shouldShowZombiesFUSER();
	bool showAnimals = renderBridge->shouldShowAnimalsFUSER();
	bool showPlayerInfoesp = renderBridge->shouldShowPlayerInfoesp();
	int ZombieDistance = renderBridge->shouldZombieDistanceFUSER();

	std::string PlayerNameYES = renderBridge->shouldPlayerName();


	std::vector<std::string> MainPlayerName = { PlayerNameYES };

	for (const auto& ent : entities) {

		if (!ent->isValid())
			continue;
		if (ent->isDead)
			continue;

		ImU32 boxColor;

		bool isMainPlayer = false;

		std::vector<std::string> infoText;


		if (ent->isPlayer()) {
			auto ident = ent->getPlayerIdentity(scoreboard);
			if (ident && ident->PlayerName) {
				isMainPlayer = std::find(MainPlayerName.begin(), MainPlayerName.end(), ident->PlayerName->value) != MainPlayerName.end();
			}
		}

		if (isMainPlayer) {
			continue;
		}
		else if (ent->isPlayer()) {
			boxColor = IM_COL32(255, 0, 0, 255);
		}
		else if (ent->isZombie() && showZombies) {
			boxColor = IM_COL32(255, 255, 0, 255);
		}
		/*else if (ent->isCar()) {
			boxColor = IM_COL32(255, 255, 0, 255);
		}
		else if (ent->isBoat()) {
			boxColor = IM_COL32(255, 200, 0, 255);
		}*/
		else if (ent->isAnimal() && showAnimals) {
			boxColor = IM_COL32(0, 255, 0, 200);
		}
		else {
			continue;
		}
		auto originPos = ent->FutureVisualStatePtr->position;
		float entHeight = ent->isAnimal() ? 1 : 1.8;
		auto topPos = originPos + DMARender::Vector3(0, entHeight, 0);

		DMARender::Vector2 originW2S, topW2S;
		float dist = camera->InvertedViewTranslation.Dist(originPos);
		if (dist < 3.1)
			continue;

		if (ent->isZombie() && dist > ZombieDistance)
			continue;

		//if (ent->isCar() && dist > 1000)
		//	continue;
		//if (ent->isBoat() && dist > 1000)
		//	continue;

		if (!WorldToScreenDayZ(camera, originPos, originW2S))
			continue;
		if (!WorldToScreenDayZ(camera, topPos, topW2S))
			continue;
		float width = (originW2S.y - topW2S.y) / entHeight;

		


		//std::vector<std::string> infoText;
		if (ent->isAnimal()) {
			auto entBestStr = ent->EntityTypePtr->getBestString();
			if (entBestStr) {
				auto entName = std::string(ent->EntityTypePtr->getBestString()->value);
				infoText.push_back(entName);
			}

			infoText.push_back(std::format("{:.0f}m", dist));

		}
		if (ent->isPlayer()) {
			auto ident = ent->getPlayerIdentity(scoreboard);
			if (ident && ident->PlayerName) {
				infoText.push_back(ident->PlayerName->value);
			}

			if (ent->InventoryPtr->isHandItemValid) {
				auto bestHandStr = ent->InventoryPtr->handItem->EntityTypePtr->getBestString();
				if (bestHandStr) {
					infoText.push_back(bestHandStr->value);
				}
				else {
					infoText.push_back("(Unknown)");
				}
			}

			infoText.push_back(std::format("{:.0f}m", dist));
		}


		drawBoundingBox(topW2S, originW2S, width, boxColor);


		if (ent->isPlayer() && !showPlayerInfoesp)
			continue;

		ImGui::PushFont(playerFont);
		drawTextList(infoText, DMARender::Vector2(topW2S.x + width, topW2S.y), ImGui::GetFontSize(), boxColor);
		ImGui::PopFont();

	}
}

void DayZ::OverlayAdapter::drawDebugInformation(DayZ::Camera* camera, const std::vector<std::shared_ptr<DayZ::Entity>>& entities)
{
	int LootDebugDistance = renderBridge->shouldLootDebugDistance();


	for (auto const item : entities) {


		auto itemPos = item->FutureVisualStatePtr->position;
		auto screenPos = DMARender::Vector2();
		if (!WorldToScreenDayZ(camera, itemPos, screenPos))
			continue;

		float dist = camera->InvertedViewTranslation.Dist(itemPos);
		if (dist > LootDebugDistance)
			continue;

		drawText(std::string("TypeName: ") + item->EntityTypePtr->TypeName->value, DMARender::Vector2(screenPos.x, screenPos.y + 20), ImGui::GetFontSize(), IM_COL32(0, 255, 0, 255));
		drawText(std::string("ConfigName: ") + item->EntityTypePtr->ConfigName->value, DMARender::Vector2(screenPos.x, screenPos.y + 40), ImGui::GetFontSize(), IM_COL32(0, 255, 0, 255));;
		drawText(std::string("CleanName: ") + item->EntityTypePtr->CleanName->value, DMARender::Vector2(screenPos.x, screenPos.y + 60), ImGui::GetFontSize(), IM_COL32(0, 255, 0, 255));;
		drawText(std::string("ModelName: ") + item->EntityTypePtr->ModelName->value, DMARender::Vector2(screenPos.x, screenPos.y + 80), ImGui::GetFontSize(), IM_COL32(0, 255, 0, 255));;
		drawText(std::string("X: ") + std::to_string(itemPos.x), DMARender::Vector2(screenPos.x, screenPos.y + 100), ImGui::GetFontSize(), IM_COL32(0, 255, 0, 255));;
		drawText(std::string("Y: ") + std::to_string(itemPos.y), DMARender::Vector2(screenPos.x, screenPos.y + 120), ImGui::GetFontSize(), IM_COL32(0, 255, 0, 255));;
		drawText(std::string("Z: ") + std::to_string(itemPos.z), DMARender::Vector2(screenPos.x, screenPos.y + 140), ImGui::GetFontSize(), IM_COL32(0, 255, 0, 255));;
		//drawText(std::to_string(item->isDead), DMARender::Vector2(screenPos.x, screenPos.y + 120), ImGui::GetFontSize(), IM_COL32(0, 255, 0, 255));;
	}
}
