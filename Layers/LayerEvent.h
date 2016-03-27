#pragma once
// Flags
namespace LayerNs
{
	enum LayerEvent
	{
		NOCOLLISION = 0,
		COLLISION = 1 << 0,
		UPDATE = 1 << 1,
		UPDATE_STATE = 1 << 2,
		CLOSE = 1 << 3
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