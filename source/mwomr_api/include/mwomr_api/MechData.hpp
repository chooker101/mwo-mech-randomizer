#pragma once
#include <string>
#include <vector>
#include "mwomr_api/ComponentData.hpp"

namespace mwomr_api {
	namespace upgrades {
		namespace clan {
			enum class armour
			{
				std = 5,
				ferro = 4
			};
			enum class structure
			{
				std = 24,
				endo = 16
			};
			enum class heatsink
			{
				single_hs = 6,
				double_hs = 4
			};
		}
		namespace inner_sphere {
			enum class armour
			{
				std = 0,
				ferro = 1,
				light_ferro = 2,
				stealth = 3
			};
			enum class structure
			{
				std = 0,
				endo = 8
			};
			enum class heatsink
			{
				single_hs = 0,
				double_hs = 2
			};
		}
		enum class guidance
		{
			std = 0,
			artemis = 1
		};
		enum class omni
		{
			has = 8,
			no = 0
		};
		enum class actuator
		{
			has = 0,
			no = 1
		};

		union omni_actuator {
			struct {
				actuator laa;
				actuator ha;
			};
			actuator actuators[];
		};
		
	}

	class MechData
	{
	public:
		std::string mIdCode = "W2";
		int mArmourType = static_cast<int>(upgrades::clan::armour::std);
		int mStructureType = static_cast<int>(upgrades::clan::structure::std);
		int mHeatsinkType = static_cast<int>(upgrades::clan::heatsink::single_hs);
		int mGuidanceType = static_cast<int>(upgrades::guidance::std);
		int mOmniType = static_cast<int>(upgrades::omni::has);

		std::vector<std::unique_ptr<ComponentData>> mComponents = std::vector<std::unique_ptr<ComponentData>>();
		std::vector<std::unique_ptr<upgrades::omni_actuator>> mOmniActuators = std::vector<std::unique_ptr<upgrades::omni_actuator>>(); //ra first, then la, will be read backwards
	};
}