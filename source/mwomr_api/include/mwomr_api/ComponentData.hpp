#pragma once
#include <memory>
#include "mwomr_api/ItemData.hpp"
#include "mwomr_api/EngineData.hpp"

namespace mwomr_api {
	enum class ComponentType {
		center_torso,
		head,
		left_arm,
		left_leg,
		left_torso,
		right_arm,
		right_leg,
		right_torso
	};

	class ComponentData {
	public:
		ComponentType mComponentType = ComponentType::center_torso;
		std::string mOmniID = ";E7";
		std::unique_ptr<EngineData> mEngineData = nullptr;
		int mArmour = 0;
		int mArmourBonus = 0;
		int mRearArmour = 0;
		int mRearArmourBonus = 0; //Dont think this is ever used?
		std::vector<std::unique_ptr<ItemData>> mItems = std::vector<std::unique_ptr<ItemData>>();
	};
}