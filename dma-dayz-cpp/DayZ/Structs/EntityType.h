#pragma once
#include "DMAMemoryManagement/includes.h";
#include "ArmaString.h"

namespace DayZ {
	struct EntityType : public DMAMem::MemoryObject {
		std::shared_ptr<ArmaString> TypeName;
		std::shared_ptr<ArmaString> ModelName;
		std::shared_ptr<ArmaString> ConfigName;
		std::shared_ptr<ArmaString> CleanName;
		EntityType() {
			TypeName = std::shared_ptr<ArmaString>(new ArmaString());
			ModelName = std::shared_ptr<ArmaString>(new ArmaString());
			ConfigName = std::shared_ptr<ArmaString>(new ArmaString());
			CleanName = std::shared_ptr<ArmaString>(new ArmaString());
			this->registerPointer(0x70, TypeName.get());
			this->registerPointer(0x88, ModelName.get());
			this->registerPointer(0xA8, ConfigName.get());
			this->registerPointer(0x4F0, CleanName.get());
		}

		bool isInvalidCleanName(const std::shared_ptr<ArmaString>& cleanName) const {
			std::string cleanStr(cleanName->value);
			return cleanStr.find("dayzinfected") != std::string::npos || cleanStr.find(".p3d") != std::string::npos;
		}

		std::shared_ptr<ArmaString> getBestString() {
			if (TypeName && TypeName->length > 0 && TypeName->length < 400) {
				return TypeName;
			}

			if (CleanName && CleanName->length > 0 && CleanName->length < 400 && !isInvalidCleanName(CleanName)) {
				return CleanName;
			}

			if (ModelName && ModelName->length > 0 && ModelName->length < 400) {
				return ModelName;
			}

			if (ConfigName && ConfigName->length > 0 && ConfigName->length < 400) {
				return ConfigName;
			}

			return nullptr;
		}
	};
}