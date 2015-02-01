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
	typedef std::shared_ptr<b2World> WorldPtr;

	b2PolygonShape CreateBoxShape(float width, float height);
	b2Body* CreateStaticBox(float x, float y, float width, float height, b2World& world);
	Emitter CreateEmitter(float x, float y, b2ParticleSystem *particleSystem);
}