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
	typedef std::shared_ptr<b2ParticleSystem> ParticleSystemPtr;
	typedef std::shared_ptr<b2Body> BodyPtr;

	ParticleSystemPtr WrapB2Resource(b2World* world, b2ParticleSystem* res);
	BodyPtr WrapB2Resource(b2World* world, b2Body* body);

	b2PolygonShape CreateBoxShape(float width, float height);
	b2Body* CreateStaticBox(float x, float y, float width, float height, b2World& world);
	Emitter CreateEmitter(float x, float y, ParticleSystemPtr particleSystem);
}