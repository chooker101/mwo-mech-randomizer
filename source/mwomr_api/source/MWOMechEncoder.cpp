#include "mwomr_api/MWOMechEncoder.hpp"

using namespace mwomr_api;

std::string MWOMechEncoder::GetEncodedMech(const MechData& mechData) const
{
    if(mechData.mIdCode.empty())
    {
		//TODO: Log error
        return std::string();
	}
	std::string code = MECH_VERSION + mechData.mIdCode;
	code += Base10To64(mechData.mStructureType + mechData.mArmourType);
	code += Base10To64(mechData.mHeatsinkType + mechData.mGuidanceType + mechData.mOmniType);

	bool omniMech = mechData.mOmniType == static_cast<int>(upgrades::omni::has);

	if (omniMech) {
		uint32_t actuatorType = 0;
		for (int i = 1; i >= 0; --i) {
			for (int j = 0; j <= 1; ++j) {
				actuatorType += (3 * i + 1) * (static_cast<int>(mechData.mOmniActuators[i]->actuators[j]));
			}
		}
		code += Base10To64(actuatorType);
	}
	else {
		code += ":";
	}

	int componentIndex = 0;
	for (const auto& component : mechData.mComponents) {
		//iterate through items on component and add to code
		code += Base10To64(component->mArmour - component->mArmourBonus, 2);
		if (omniMech && component->mComponentType != ComponentType::center_torso) { 
			code += component->mOmniID;
		}
		if (!omniMech && component->mComponentType == ComponentType::center_torso) {
			code += "|" + component->mEngineData->mItemID;
			std::string heatsinkCode;
			if (mechData.mHeatsinkType == static_cast<int>(upgrades::clan::heatsink::single_hs) || mechData.mHeatsinkType == static_cast<int>(upgrades::inner_sphere::heatsink::single_hs)) {
				heatsinkCode = HEATSINK_CODES[static_cast<int>(HeatsinkCodeIndex::SHS)];
			}
			else {
				if (mechData.mHeatsinkType == static_cast<int>(upgrades::clan::heatsink::double_hs)) {
					heatsinkCode = HEATSINK_CODES[static_cast<int>(HeatsinkCodeIndex::CLAN_DHS)];
				}
				else {
					heatsinkCode = HEATSINK_CODES[static_cast<int>(HeatsinkCodeIndex::DHS)];
				}
			}

			for (int i = 0; i < component->mEngineData->mInternalHeatsinkCount; ++i)
			{
				code += "|" + heatsinkCode;
			}
		}
		for (const auto& item : component->mItems) {
			if (item->mItemType != ItemType::internal && item->mItemType != ItemType::fixed) {
				code += "|" + item->mItemID;
			}
		}
		code += COMPONENT_CODES[componentIndex];
		++componentIndex;
	}
	for (const auto& component : mechData.mComponents) {
		if (component->mComponentType == ComponentType::center_torso) {
			code += Base10To64(component->mRearArmour - component->mRearArmourBonus, 2);
		}
	}
	for (const auto& component : mechData.mComponents) {
		if (component->mComponentType == ComponentType::left_torso) {
			code += Base10To64(component->mRearArmour - component->mRearArmourBonus, 2);
		}
	}
	for (const auto& component : mechData.mComponents) {
		if (component->mComponentType == ComponentType::right_torso) {
			code += Base10To64(component->mRearArmour - component->mRearArmourBonus, 2);
		}
	}
	return code;
}

std::string MWOMechEncoder::Base10To64(uint32_t value, uint32_t padding) const
{
	std::string result;
	
	while(value > 0)
	{
		result += BASE64_KEY[value % 64];
		value /= 64;
	}
	if(padding > 0)
	{
		while(result.length() < padding)
		{
			result += BASE64_KEY[0];
		}
	}
	return result;
}
