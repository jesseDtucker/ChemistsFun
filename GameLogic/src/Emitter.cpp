#include "Box2D/Box2D.h"
#include "Emitter.hpp"

using namespace std;
using namespace FluidGame;

Emitter::Emitter(b2ParticleSystem* particleSystem)
	: m_particleSystem(particleSystem)
	, m_count(0.0f)
{

}

void Emitter::Step(float dt)
{
	m_count += dt;
	while (m_count > 1.0f)
	{
		m_count -= 1.0f;
		b2ParticleDef particleDef;
		particleDef.color = b2Color(0.0f, 0.0f, 1.0f);
		particleDef.position = { 50, 50 };
		auto id = m_particleSystem->CreateParticle(particleDef);
		m_particleIds.push_back(id);
	}
}