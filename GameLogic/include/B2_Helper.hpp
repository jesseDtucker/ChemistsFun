#pragma once

#include <functional>
#include <memory>


#include "Box2D/Box2D.h"


//////////////////////////////////////////////////////////////////////////
//
//	Helper for managing the resources provided by B2_Helper
//
//////////////////////////////////////////////////////////////////////////

namespace FluidGame
{
	typedef std::unique_ptr<b2World> WorldPtr;
	typedef std::unique_ptr<b2ParticleSystem, std::function<void(b2ParticleSystem*)>> ParticleSystemPtr;
	typedef std::unique_ptr<b2Body, std::function<void(b2Body*)>> BodyPtr;

	ParticleSystemPtr WrapB2Resource(b2World* world, b2ParticleSystem* res);
	BodyPtr WrapB2Resource(b2World* world, b2Body* body);
}