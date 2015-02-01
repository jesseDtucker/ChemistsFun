#include "Arc_Assert.hpp"
#include "Level.hpp"

using namespace std;
using namespace FluidGame;

const int VELOCITY_ITERATIONS = 8;
const int POSITION_ITERATIONS = 3;
const int PARTICLE_ITERATIONS = 3;

Level::Level(WorldPtr world, ParticleSystemPtr particleSystem)
	: m_World(world)
	, m_ParticleSystem(particleSystem)
{

}

void Level::Step(float dt)
{
	m_World->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS, PARTICLE_ITERATIONS);
	for (auto& emitter : m_Emitters)
	{
		emitter.Step(dt);
	}
	m_MainCharacter->Step(dt);

	int destroyed = 0;

	// kill particles that go off screen
	b2Transform emptyTransform;
	emptyTransform.Set({ 0.0f, 0.0f }, 0.0f);
	for (auto& killBox : m_KillBoxes)
	{
		destroyed += m_ParticleSystem->DestroyParticlesInShape(killBox.second, killBox.first);
	}
}