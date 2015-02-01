#pragma once

#include <random>
#include <vector>

#include "PropertyHelper.hpp"

class b2ParticleSystem;

namespace FluidGame
{
	class Emitter
	{
	public:
		Emitter(b2ParticleSystem* particleSystem, 
				b2Vec2 position, 
				float particlesPerSecond = 50.0f,
				b2Vec2 velocityMin = { 0.0f, 0.0f },
				b2Vec2 velocityMax = { 1.0f, 1.0f } );
		bool operator==(const Emitter rhs);

		void Step(float dt);
		PROP_GET(b2Vec2, Position);
		void SetPosition(b2Vec2 position);
	private:
		b2ParticleSystem* m_particleSystem;
		float m_count;
		b2Vec2 m_velocityMin;
		b2Vec2 m_velocityMax;
		float m_secondsPerParticle;
		std::uniform_real_distribution<float> m_rands;
		std::mt19937 m_gen;
		std::vector<int32_t> m_particleIds;
	};
}