#pragma once

#include <functional>
#include <memory>

#include "Box2D/Box2D.h"
#include "Emitter.hpp"

//////////////////////////////////////////////////////////////////////////
//
//	Helper for managing the resources provided by B2_Helper
//
//////////////////////////////////////////////////////////////////////////

namespace FluidGame
{
	b2PolygonShape CreateBoxShape(float width, float height);
	b2Body* CreateStaticBox(float x, float y, float width, float height, b2World& world);
	std::shared_ptr<Emitter> CreateEmitter(float x, float y, b2ParticleSystem particleSystem);
}