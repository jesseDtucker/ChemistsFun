#include "B2_Helper.hpp"

FluidGame::ParticleSystemPtr FluidGame::WrapB2Resource(b2World* world, b2ParticleSystem* res)

{
	std::function<void(b2ParticleSystem*)> deleter = [world](b2ParticleSystem* p)
	{
		world->DestroyParticleSystem(p);
	};

	return ParticleSystemPtr(res, deleter);
}
