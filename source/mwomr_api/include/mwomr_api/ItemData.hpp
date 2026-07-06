#pragma once
#include <string>

namespace mwomr_api {
	enum class ItemType {
		internal,
		fixed,
		movable
	};

	class ItemData {
	public:
		std::string mItemID;
		ItemType mItemType = ItemType::movable;
	};
}