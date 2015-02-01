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
	m_World->Step(dt,
		VELOCITY_ITERATIONS,
		POSITION_ITERATIONS,
		PARTICLE_ITERATIONS);

	for (auto& emitter : m_Emitters)
	{
		emitter.Step(dt);
	}
}