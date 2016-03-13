#pragma once
// Flags
namespace LayerNs
{
	enum LayerEvent
	{
		OK = 0,

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