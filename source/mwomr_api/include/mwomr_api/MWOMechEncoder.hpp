#include <string>
#include "mwomr_api/MechData.hpp"

namespace mwomr_api {
	const std::string MECH_VERSION = "A";
	const std::string BASE64_KEY = "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmno";
	const std::vector<std::string> COMPONENT_CODES = { "p", "q", "r", "s", "t", "u", "v", "w" };
	enum class HeatsinkCodeIndex {
		SHS,
		DHS,
		CLAN_DHS
	};
	const std::vector<std::string> HEATSINK_CODES = { "h^", "i^", "l^" };

	class MWOMechEncoder {
	public:
		std::string GetEncodedMech(const MechData& mechData) const;
	private:
		std::string Base10To64(uint32_t value, uint32_t padding = 0) const;
	};
}