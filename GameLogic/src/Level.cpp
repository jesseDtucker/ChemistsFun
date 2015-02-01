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

	if (emitterPresent)
	{
		for (auto& emitter : m_Emitters)
		{
			emitter.Step(dt);
		}
	}
	m_MainCharacter->Step(dt);

	// kill particles that go off screen
	b2Transform emptyTransform;
	emptyTransform.Set({ 0.0f, 0.0f }, 0.0f);
	float lowestPoint = -FLT_MAX;
	for (auto& killBox : m_KillBoxes)
	{
		m_ParticleSystem->DestroyParticlesInShape(killBox.second, killBox.first);
		lowestPoint = std::max(lowestPoint, killBox.first.p.y);
	}

	auto mainCharacterCenter = m_MainCharacter->GetBody()->GetWorldCenter();
	if (mainCharacterCenter.y > lowestPoint)
	{
		// character is considered to have fallen off the world
		m_MainCharacter->Kill();
	}
}