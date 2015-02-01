#pragma once

#include <vector>

#include "PropertyHelper.hpp"

class b2ParticleSystem;

namespace FluidGame
{
	class Emitter
	{
	public:
		Emitter(b2ParticleSystem* particleSystem, b2Vec2 position);

		void Step(float dt);
		PROP_GET(b2Vec2, Position);
	private:
		b2ParticleSystem* m_particleSystem;
		float m_count;
		std::vector<int32_t> m_particleIds;
	};
}