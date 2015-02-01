#include <random>

#include "Box2D/Box2D.h"
#include "Emitter.hpp"

using namespace std;
using namespace FluidGame;

Emitter::Emitter(b2ParticleSystem* particleSystem, b2Vec2 position, float particlesPerSecond, b2Vec2 velocityMin, b2Vec2 velocityMax)
	: m_particleSystem(particleSystem)
	, m_count(0.0f)
	, m_secondsPerParticle(1.0f / particlesPerSecond)
	, m_Position(position)
	, m_velocityMin(velocityMin)
	, m_velocityMax(velocityMax)
	, m_rands(0.0f, 1.0f)
	, m_gen(std::random_device()())
{
	
}

void Emitter::Step(float dt)
{
	m_count += dt;
	while (m_count > m_secondsPerParticle)
	{
		m_count -= m_secondsPerParticle;
		b2ParticleDef particleDef;
		particleDef.position = m_Position;
		particleDef.velocity = { m_velocityMin.x + m_rands(m_gen) * m_velocityMax.x,
			m_velocityMin.y + m_rands(m_gen) * m_velocityMax.y };
		auto id = m_particleSystem->CreateParticle(particleDef);
		m_particleIds.push_back(id);
	}
}

bool FluidGame::Emitter::operator==(const Emitter rhs)
{
	return rhs.m_particleIds == m_particleIds;
}