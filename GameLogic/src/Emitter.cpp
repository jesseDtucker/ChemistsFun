#include "Box2D/Box2D.h"
#include "Emitter.hpp"

using namespace std;
using namespace FluidGame;

Emitter::Emitter(b2ParticleSystem* particleSystem, b2Vec2 position)
	: m_particleSystem(particleSystem)
	, m_count(0.0f)
	, m_Position(position)
{

}

void Emitter::Step(float dt)
{
	m_count += dt;
	while (m_count > 1.0f)
	{
		m_count -= 1.0f;
		b2ParticleDef particleDef;
		particleDef.position = m_Position;
		particleDef.velocity = { 0.01f, 0.01f };
		auto id = m_particleSystem->CreateParticle(particleDef);
		m_particleIds.push_back(id);
	}
}