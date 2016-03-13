#include "BottomLayer.h"

BottomLayer::BottomLayer()
{

}

void BottomLayer::initialize(int width, int height)
{

	isInitialized = true;
}

void BottomLayer::reset()
{
}

void BottomLayer::resize(int width, int height)
{
}

void BottomLayer::render(Graphics * g)
{
}

void BottomLayer::update(float dt)
{
}

LayerNs::LayerEvent BottomLayer::handleEvent(Input & input)
{
	return LayerNs::LayerEvent();
}
