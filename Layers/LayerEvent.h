#pragma once
// Flags
namespace LayerNs
{
	enum LayerEvent
	{
		NOCOLLISION = 1 << 0,
		COLLISION = 1 << 1,
		UPDATE = 1 << 2,
		UPDATE_STATE = 1 << 3,
		CLOSE = 1 << 4
	};

	inline LayerEvent operator|(LayerEvent a, LayerEvent b)
	{
		return static_cast<LayerEvent>(static_cast<int>(a) | static_cast<int>(b));
	}

	inline bool operator%(LayerEvent a, LayerEvent b)
	{
		return static_cast<LayerEvent>(static_cast<int>(a) & static_cast<int>(b)) == b;
	}
}