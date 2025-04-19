#pragma once
#include <memory>
#include "../../IOverlay/IOverlay.h"
#include "../../IRadar/IRadar.h"
#include "MapManager/MapManager.h"
#include <d3d11.h>

namespace DMARender {
	class RenderBridge {
		std::shared_ptr<IOverlay> overlayPtr = nullptr;
		std::shared_ptr<IRadar> radarPtr = nullptr;
		std::shared_ptr<MapManager> mapManager;
		ID3D11Device** g_pd3dDevicePtr;

		// fonts

		int FontRADAR = 13;
		int FontRADAR2 = 13;


		bool showDeadPlayers = true;
		bool showVehicles = true;
		bool showGrounditems = false;
		bool showBoats = true;
		bool showDeadAnimals = true;
		bool showClothing = false;
		bool showWeapons = true;
		bool showProxyMagazines = true;
		bool showBackpacks = true;
		bool showRare = true;
		bool showFood = true;
		bool showAmmo = true;
		bool showPlayerList = true;
		bool showServerPlayerList = false;
		bool showZombies = false;
		bool showAnimals = true;
		std::string playername =  "Survivor";
		int BlipSize = 7;
		int BlipSize2 = 4;
		int Aimlinelength = 80;
		bool showOptics = true;
		bool showBase = true;
		bool showMelee = true;
		int LootDistanceDeadzone = 0;
		bool showExplosives = true;
		int ZombiesBlipSize = 4;
		int AnimalsBlipSize = 5;



		// fuser
		bool showDeadPlayersFUSER = true;
		bool showVehiclesFUSER = true;
		bool showGrounditemsFUSER = true;
		bool showBoatsFUSER = true;
		bool showDeadAnimalsFUSER = true;
		bool showClothingFUSER = false;
		bool showWeaponsFUSER = true;
		bool showProxyMagazinesFUSER = true;
		bool showBackpacksFUSER = true;
		bool showRareFUSER = true;
		bool showFoodFUSER = true;
		bool showAmmoFUSER = true;
		bool showZombiesFUSER = false;
		bool showAnimalsFUSER = true;
		int lootDistanceFUSER = 70;
		int ZombieDistanceFUSER = 100;
		bool showPlayerInfoesp = true;
		bool showOpticsFUSER = true;
		bool showDebugFUSER = false;
		bool showBaseFUSER = true;
		bool showMeleeFUSER = true;
		bool showExplosivesFUSER = true;
		int LootDebugDistance = 70;



	public:
		RenderBridge(ID3D11Device** g_pd3dDevice);
		void createFonts();
		void setOverlay(std::shared_ptr<IOverlay> ptr);
		std::shared_ptr<IOverlay> getOverlay();
		void setRadar(std::shared_ptr<IRadar> ptr);
		std::shared_ptr<IRadar> getRadar();
		void addMap(std::shared_ptr<IGameMap> map);
		std::shared_ptr<MapManager> getMapManager();

		//fonts

		int shouldRadarFont() const { return FontRADAR; }
		int shouldRadarFont2() const { return FontRADAR2; }

		// getter and setter methods for visibility settings
		bool shouldShowDeadPlayers() const { return showDeadPlayers; }
		bool shouldShowVehicles() const { return showVehicles; }
		bool shouldShowBoats() const { return showBoats; }
		bool shouldShowGrounditems() const { return showGrounditems; }
		bool shouldShowDeadAnimals() const { return showDeadAnimals; }
		bool shouldShowClothing() const { return showClothing; }
		bool shouldShowWeapons() const { return showWeapons; }
		bool shouldShowProxyMagazines() const { return showProxyMagazines; }
		bool shouldShowBackpacks() const { return showBackpacks; }
		bool shouldShowRare() const { return showRare; }
		bool shouldShowFood() const { return showFood; }
		bool shouldShowAmmo() const { return showAmmo; }
		bool shouldShowPlayerList() const { return showPlayerList; }
		bool shouldShowServerPlayerList() const { return showServerPlayerList; }
		bool shouldShowZombies() const { return showZombies; }
		bool shouldShowAnimals() const { return showAnimals; }
		std::string shouldPlayerName() const { return playername; }
		int shouldBlipSize() const { return BlipSize; }
		int shouldBlipSize2() const { return BlipSize2; }
		int shouldAimlinelength() const { return Aimlinelength; }
		bool shouldShowOptics() const { return showOptics; }
		bool shouldShowBase() const { return showBase; }
		bool shouldShowMelee() const { return showMelee; }
		int shouldLootDistanceDeadzone() const { return LootDistanceDeadzone; }
		bool shouldShowExplosives() const { return showExplosives; }
		int shouldZombiesBlipSize() const { return ZombiesBlipSize; }
		int shouldAnimalsBlipSize() const { return AnimalsBlipSize; }


		//fuser
		bool shouldShowDeadPlayersFUSER() const { return showDeadPlayersFUSER; }
		bool shouldShowVehiclesFUSER() const { return showVehiclesFUSER; }
		bool shouldShowBoatsFUSER() const { return showBoatsFUSER; }
		bool shouldShowGrounditemsFUSER() const { return showGrounditemsFUSER; }
		bool shouldShowDeadAnimalsFUSER() const { return showDeadAnimalsFUSER; }
		bool shouldShowClothingFUSER() const { return showClothingFUSER; }
		bool shouldShowWeaponsFUSER() const { return showWeaponsFUSER; }
		bool shouldShowProxyMagazinesFUSER() const { return showProxyMagazinesFUSER; }
		bool shouldShowBackpacksFUSER() const { return showBackpacksFUSER; }
		bool shouldShowRareFUSER() const { return showRareFUSER; }
		bool shouldShowFoodFUSER() const { return showFoodFUSER; }
		bool shouldShowAmmoFUSER() const { return showAmmoFUSER; }
		bool shouldShowZombiesFUSER() const { return showZombiesFUSER; }
		bool shouldShowAnimalsFUSER() const { return showAnimalsFUSER; }
		int shouldlootDistanceFUSER() const { return lootDistanceFUSER; }
		int shouldZombieDistanceFUSER() const { return ZombieDistanceFUSER; }
		bool shouldShowPlayerInfoesp() const { return showPlayerInfoesp; }
		bool shouldShowOpticsFUSER() const { return showOpticsFUSER; }
		bool shouldShowDebugFUSER() const { return showDebugFUSER; }
		bool shouldShowBaseFUSER() const { return showBaseFUSER; }
		bool shouldShowMeleeFUSER() const { return showMeleeFUSER; }
		bool shouldShowExplosivesFUSER() const { return showExplosivesFUSER; }
		int shouldLootDebugDistance() const { return LootDebugDistance; }

		// fonts

		void setRadarFont(int value) { FontRADAR = value; }
		void setRadarFont2(int value) { FontRADAR2 = value; }


		void setShowPlayerList(bool value) { showPlayerList = value; }
		void setShowServerPlayerList(bool value) { showServerPlayerList = value; }
		void setShowDeadPlayers(bool value) { showDeadPlayers = value; }
		void setShowVehicles(bool value) { showVehicles = value; }
		void setShowBoats(bool value) { showBoats = value; }
		void setShowGrounditems(bool value) { showGrounditems = value; }
		void setShowDeadAnimals(bool value) { showDeadAnimals = value; }
		void setShowClothing(bool value) { showClothing = value; }
		void setShowWeapons(bool value) { showWeapons = value; }
		void setShowProxyMagazines(bool value) { showProxyMagazines = value; }
		void setShowBackpacks(bool value) { showBackpacks = value; }
		void setShowRare(bool value) { showRare = value; }
		void setShowFood(bool value) { showFood = value; }
		void setShowAmmo(bool value) { showAmmo = value; }
		void setShowZombies(bool value) { showZombies = value; }
		void setShowAnimals(bool value) { showAnimals = value; }
		void setShowPlayerName(std::string value) { playername = value; }
		void setShowBlipSize(int value) { BlipSize = value; }
		void setShowBlipSize2(int value) { BlipSize2 = value; }
		void setAimlinelength(int value) { Aimlinelength = value; }
		void setShowOptics(bool value) { showOptics = value; }
		void setShowBase(bool value) { showBase = value; }
		void setShowMelee(bool value) { showMelee = value; }
		void setLootDistanceDeadzone(int value) { LootDistanceDeadzone = value; }
		void setShowExplosives(bool value) { showExplosives = value; }
		void setZombiesBlipSize(int value) { ZombiesBlipSize = value; }
		void setAnimalsBlipSize(int value) { AnimalsBlipSize = value; }


		//fuser
		void setShowDeadPlayersFUSER(bool value) { showDeadPlayersFUSER = value; }
		void setShowVehiclesFUSER(bool value) { showVehiclesFUSER = value; }
		void setShowBoatsFUSER(bool value) { showBoatsFUSER = value; }
		void setShowGrounditemsFUSER(bool value) { showGrounditemsFUSER = value; }
		void setShowDeadAnimalsFUSER(bool value) { showDeadAnimalsFUSER = value; }
		void setShowClothingFUSER(bool value) { showClothingFUSER = value; }
		void setShowWeaponsFUSER(bool value) { showWeaponsFUSER = value; }
		void setShowProxyMagazinesFUSER(bool value) { showProxyMagazinesFUSER = value; }
		void setShowBackpacksFUSER(bool value) { showBackpacksFUSER = value; }
		void setShowRareFUSER(bool value) { showRareFUSER = value; }
		void setShowFoodFUSER(bool value) { showFoodFUSER = value; }
		void setShowAmmoFUSER(bool value) { showAmmoFUSER = value; }
		void setShowZombiesFUSER(bool value) { showZombiesFUSER = value; }
		void setShowAnimalsFUSER(bool value) { showAnimalsFUSER = value; }
		void setlootDistance(int value) { lootDistanceFUSER = value; }
		void setZombieDistance(int value) { ZombieDistanceFUSER = value; }
		void setShowPlayerInfoesp(bool value) { showPlayerInfoesp = value; }
		void setShowOpticsFUSER(bool value) { showOpticsFUSER = value; }
		void setShowDebugFUSER(bool value) { showDebugFUSER = value; }
		void setShowBaseFUSER(bool value) { showBaseFUSER = value; }
		void setShowMeleeFUSER(bool value) { showMeleeFUSER = value; }
		void setShowExplosivesFUSER(bool value) { showExplosivesFUSER = value; }
		void setLootDebugDistance(int value) { LootDebugDistance = value; }

	};
}