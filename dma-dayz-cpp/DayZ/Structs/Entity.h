#pragma once
#include "DMAMemoryManagement/includes.h";
#include "FutureVisualState.h";
#include "EntityType.h"
#include "Scoreboard.h"
#include "ScoreboardIdentity.h"
#include "EntityInventory.h"
#include "EntityFilterList.h"


namespace DayZ {


	enum ENTITY_TYPE {
		NONE,
		GROUNDITEM,
		PLAYER,
		ZOMBIE,
		CAR,
		BOAT,
		ANIMAL,
		CLOTHING,
		WEAPON,
		PROXYMAGAZINES,
		BACKPACK,
		FOOD,
		AMMO,
		RARE,
		OPTICS,
		BASE,
		MELEE,
		EXPLOSIVES
	};

	class Entity : public DMAMem::MemoryObject {

		ENTITY_TYPE _entityType = ENTITY_TYPE::NONE;
		bool _isEntityTypeChecked = false;
		bool _isValid = false;
		bool _isValidChecked = false;

		// static list for rare items
		static std::set<std::string> rareItems;
		static void loadRareItems(const std::string& filePath);

	public:
		static void initializeRareItems(const std::string& filePath) {
			loadRareItems(filePath);
		}

		// categorize entity, casesensitive
		void categorizeEntity() {
			if (_entityType == ENTITY_TYPE::NONE) {
				if (!strcmp("dayzplayer", this->EntityTypePtr->ConfigName->value)) {
					_entityType = ENTITY_TYPE::PLAYER;
					return;
				}
				if (!strcmp("dayzinfected", this->EntityTypePtr->ConfigName->value)) {
					_entityType = ENTITY_TYPE::ZOMBIE;
					return;
				}
				if (!strcmp("car", this->EntityTypePtr->ConfigName->value)) {
					_entityType = ENTITY_TYPE::CAR;
					return;
				}
				if (!strcmp("boat", this->EntityTypePtr->ConfigName->value)) {
					_entityType = ENTITY_TYPE::BOAT;
					return;
				}
				if (!strcmp("dayzanimal", this->EntityTypePtr->ConfigName->value)) {
					_entityType = ENTITY_TYPE::ANIMAL;
					return;
				}
				if (rareItems.find(this->EntityTypePtr->TypeName->value) != rareItems.end()) {
					_entityType = ENTITY_TYPE::RARE;
					return;
				}
				if (strstr(this->EntityTypePtr->ModelName->value, "backpacks") != NULL) {
					_entityType = ENTITY_TYPE::BACKPACK;
					return;
				}
				if (!strcmp("clothing", this->EntityTypePtr->ConfigName->value)) {
					_entityType = ENTITY_TYPE::CLOTHING;
					return;
				}
				if (!strcmp("ProxyMagazines", this->EntityTypePtr->ConfigName->value)) {
					_entityType = ENTITY_TYPE::PROXYMAGAZINES;
					return;
				}
				if (strstr(this->EntityTypePtr->ModelName->value, "food") != NULL) {
					_entityType = ENTITY_TYPE::FOOD;
					return;
				}
				if (strstr(this->EntityTypePtr->ModelName->value, "ammunition") != NULL) {
					_entityType = ENTITY_TYPE::AMMO;
					return;
				}
				if (strstr(this->EntityTypePtr->ModelName->value, "firearms") != NULL ||
					strcmp("Weapon", this->EntityTypePtr->ConfigName->value) == 0) {
					_entityType = ENTITY_TYPE::WEAPON;
					return;
				}
				if (!strcmp("itemoptics", this->EntityTypePtr->ConfigName->value)) {
					_entityType = ENTITY_TYPE::OPTICS;
					return;
				}
				if (strstr(this->EntityTypePtr->ModelName->value, "camping") != NULL) {
					_entityType = ENTITY_TYPE::BASE;
					return;
				}
				if (strstr(this->EntityTypePtr->ModelName->value, "melee") != NULL) {
					_entityType = ENTITY_TYPE::MELEE;
					return;
				}
				if (strstr(this->EntityTypePtr->ModelName->value, "explosives") != NULL) {
					_entityType = ENTITY_TYPE::EXPLOSIVES;
					return;
				}

				for (auto const whiteListEntry : InventoryItemWhitelist) {
					if (!strcmp(whiteListEntry.c_str(), this->EntityTypePtr->ConfigName->value)) {
						_entityType = ENTITY_TYPE::GROUNDITEM;
						return;
					}
				}
			}
		}

		ENTITY_TYPE getEntityType() {
			if (!_isEntityTypeChecked) {
				categorizeEntity();
				_isEntityTypeChecked = true;
			}
			return _entityType;
		}

		std::shared_ptr<FutureVisualState> FutureVisualStatePtr;
		std::shared_ptr<EntityType> EntityTypePtr;
		std::shared_ptr<EntityInventory> InventoryPtr;
		uint32_t NetworkID;
		bool isDead;
		

		Entity() {
			FutureVisualStatePtr = std::shared_ptr<FutureVisualState>(new FutureVisualState());
			EntityTypePtr = std::shared_ptr<EntityType>(new EntityType());
			InventoryPtr = std::shared_ptr<EntityInventory>(new EntityInventory());
			this->registerPointer(0x180, EntityTypePtr.get());
			this->registerPointer(0x1D0, FutureVisualStatePtr.get());
			this->registerPointer(0x660, InventoryPtr.get());
			this->registerOffset(0x6EC, &NetworkID, sizeof(uint32_t)); // dayzplayer id for scoreboard
			this->registerOffset(0xE2, &isDead, sizeof(bool));
		}

		

		bool isValid() {

			if (!_isValidChecked) {
				for (auto blacklistItem : itemBlacklist) {
					if (!strcmp(blacklistItem.c_str(), this->EntityTypePtr->TypeName->value)) {
						_isValid = false;
						_isValidChecked = true;
						return _isValid;
					}
				}
				_isValid = this->EntityTypePtr->TypeName->length < 400 && this->EntityTypePtr->TypeName->length > 0;
				_isValidChecked = true;
			}
			return _isValid;
		}

		bool isPlayer() {
			return getEntityType() == PLAYER;
		}

		bool isZombie() {
			return getEntityType() == ZOMBIE;
		}

		bool isCar() {
			return getEntityType() == CAR;
		}

		bool isBoat() {
			return getEntityType() == BOAT;
		}

		bool isAnimal() {
			return getEntityType() == ANIMAL;
		}

		bool isRare() {
			return getEntityType() == RARE;
		}

		bool isBackpack() {
			return getEntityType() == BACKPACK;
		}

		bool isClothing() {
			return getEntityType() == CLOTHING;
		}

		bool isWeapon() {
			return getEntityType() == WEAPON;
		}

		bool isProxyMagazines() {
			return getEntityType() == PROXYMAGAZINES;
		}

		bool isFood() {
			return getEntityType() == FOOD;
		}

		bool isAmmo() {
			return getEntityType() == AMMO;
		}

		bool isGroundItem() {
			return getEntityType() == GROUNDITEM;
		}

		bool isOptic() {
			return getEntityType() == OPTICS;
		}

		bool isBase() {
			return getEntityType() == BASE;
		}

		bool isMelee() {
			return getEntityType() == MELEE;
		}

		bool isExplosives() {
			return getEntityType() == EXPLOSIVES;
		}


		std::shared_ptr<ScoreboardIdentity> getPlayerIdentity(DayZ::Scoreboard* scoreboard) {
			for (const auto ident : scoreboard->resolvedIdentities) {
				if (ident->NetworkID == this->NetworkID)
					return ident;
			}
			return NULL;
		}

	};

}