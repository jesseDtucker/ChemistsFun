#pragma once

#include <vector>

class b2ParticleSystem;

namespace FluidGame
{
	class Emitter
	{
	public:
		Emitter(b2ParticleSystem* particleSystem);

		void Step(float dt);
	private:
		b2ParticleSystem* m_particleSystem;
		float m_count;
		std::vector<int32_t> m_particleIds;
	};
}