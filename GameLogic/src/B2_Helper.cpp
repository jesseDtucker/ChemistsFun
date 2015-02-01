#include "B2_Helper.hpp"

FluidGame::ParticleSystemPtr FluidGame::WrapB2Resource(b2World* world, b2ParticleSystem* res)
{
	std::function<void(b2ParticleSystem*)> deleter = [world](b2ParticleSystem* p)
	{
		world->DestroyParticleSystem(p);
	};

	return ParticleSystemPtr(res, deleter);
}

FluidGame::BodyPtr FluidGame::WrapB2Resource(b2World* world, b2Body* body)
{
	std::function<void(b2Body*)> deleter = [world](b2Body* p)
	{
		world->DestroyBody(p);
	};

	return BodyPtr(body, deleter);
}
