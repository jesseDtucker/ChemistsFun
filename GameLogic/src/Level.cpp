#include "Arc_Assert.hpp"
#include "Level.hpp"

using namespace std;
using namespace FluidGame;

const int VELOCITY_ITERATIONS = 8;
const int POSITION_ITERATIONS = 3;
const int PARTICLE_ITERATIONS = 3;


Level::Level(WorldPtr world, b2ParticleSystem* particleSystem)
	: m_particleSystem(particleSystem)
	, m_MainCharacter(nullptr)
	, m_World(world)
{
	
}


void Level::Step(float dt)
{
	m_World->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS, PARTICLE_ITERATIONS);

	for (auto& emitter : m_Emitters)
	{
		emitter->Step(dt);
	}
	if (m_MainCharacter != nullptr)
	{
		m_MainCharacter->Step(dt);
	}
	
	// kill particles that go off screen
	b2Transform emptyTransform;
	emptyTransform.Set({ 0.0f, 0.0f }, 0.0f);
	float lowestPoint = -FLT_MAX;
	for (auto& killBox : m_KillBoxes)
	{
		m_particleSystem->DestroyParticlesInShape(killBox.second, killBox.first);
		lowestPoint = std::max(lowestPoint, killBox.first.p.y);
	}

	if (m_MainCharacter != nullptr)
	{
		auto mainCharacterCenter = m_MainCharacter->GetBody()->GetWorldCenter();
		if (mainCharacterCenter.y > lowestPoint)
		{
			// character is considered to have fallen off the world
			m_MainCharacter->Kill();
		}
	}
}

std::shared_ptr<Emitter> FluidGame::Level::CreateEmitter(float x, float y, float particlesPerSecond)
{
	std::shared_ptr<Emitter> emitter = make_shared<Emitter>(m_particleSystem, b2Vec2{ x, y }, particlesPerSecond);
	m_Emitters.push_back(emitter);
	std::shared_ptr<Emitter> result{ emitter.get(), [this, emitter](Emitter* unused)
	{
		auto initialCount = m_Emitters.size();
		auto pEnd = remove(begin(m_Emitters), end(m_Emitters), emitter);
		m_Emitters.resize(pEnd - begin(m_Emitters));
		ARC_ASSERT(initialCount - 1 == m_Emitters.size());
	} };
	return result;
}

b2ParticleSystem* FluidGame::Level::GetParticleSystem()
{
	return m_particleSystem;
}
