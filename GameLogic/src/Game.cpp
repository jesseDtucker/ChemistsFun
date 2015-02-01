#include <chrono>
#include <future>

#include "Arc_Assert.hpp"
#include "Box2D/Box2D.h"
#include "Emitter.hpp"
#include "Game.hpp"

using namespace std;
using namespace FluidGame;

const float GRAVITY_SCALE = 1.0f;
const float DENSITY = 1.0f;
const float STEP_SIZE = 1.0f / 30.0f;
const int VELOCITY_ITERATIONS = 8;
const int POSITION_ITERATIONS = 3;
const int PARTICLE_ITERATIONS = 3;

Game::Game()
	: m_world(make_unique<b2World>(b2Vec2 {0.0f, 9.81f}))
	, m_emitter(nullptr)
{
	b2ParticleSystemDef particleSystemDef;
	m_particleSystem = WrapB2Resource(m_world.get(), m_world->CreateParticleSystem(&particleSystemDef));
	
	m_particleSystem->SetGravityScale(GRAVITY_SCALE);
	m_particleSystem->SetDensity(DENSITY);

	// set contact and destruction listeners
	m_world->SetDestructionListener(this);

	m_emitter = make_shared<Emitter>(m_particleSystem.get());
}

void CreateBounds(b2Body* ground)
{
	{
		b2PolygonShape shape;
		const b2Vec2 vertices[4] = {
			b2Vec2(-40, -10),
			b2Vec2(40, -10),
			b2Vec2(40, 0),
			b2Vec2(-40, 0) };
		shape.Set(vertices, 4);
		ground->CreateFixture(&shape, 0.0f);
	}

	{
		b2PolygonShape shape;
		const b2Vec2 vertices[4] = {
			b2Vec2(0 - 20, -1),
			b2Vec2(0, -1),
			b2Vec2(0, 50),
			b2Vec2(0 - 20, 50) };
		shape.Set(vertices, 4);
		ground->CreateFixture(&shape, 0.0f);
	}

	{
		b2PolygonShape shape;
		const b2Vec2 vertices[4] = {
			b2Vec2(10, -1),
			b2Vec2(10 + 20, -1),
			b2Vec2(10 + 20, 50),
			b2Vec2(10, 50) };
		shape.Set(vertices, 4);
		ground->CreateFixture(&shape, 0.0f);
	}
}

void Game::HackSetup()
{
	// hax
	b2BodyDef bd;
	b2Body* ground = m_world->CreateBody(&bd);
	CreateBounds(ground);
}

void Game::RunSim()
{
	m_IsRunning = true;
	async([this]()
	{
		while (m_IsRunning)
		{
			auto stepSize = chrono::milliseconds((int)(STEP_SIZE * 1000.0f));
			auto startTime = chrono::system_clock::now();

			m_world->Step(STEP_SIZE,
				VELOCITY_ITERATIONS,
				POSITION_ITERATIONS,
				PARTICLE_ITERATIONS);

			m_emitter->Step(STEP_SIZE);

			auto timeTaken = chrono::system_clock::now() - startTime;
			if (timeTaken < stepSize)
			{
				this_thread::sleep_for(stepSize - timeTaken);
			}
		}
	});
}

void FluidGame::Game::SayGoodbye(b2Joint* joint)
{
	ARC_FAIL("TODO::JT");
}

void FluidGame::Game::SayGoodbye(b2Fixture* fixture)
{
	ARC_FAIL("TODO::JT");
}

void FluidGame::Game::SayGoodbye(b2ParticleGroup* group)
{
	ARC_FAIL("TODO::JT");
}

void FluidGame::Game::SayGoodbye(b2ParticleSystem* particleSystem, int32 index)
{
	ARC_FAIL("TODO::JT");
}

std::pair<int, b2Vec2*> FluidGame::Game::GetParticlesPositions()
{
	return{ m_particleSystem->GetParticleCount(), m_particleSystem->GetPositionBuffer() };
}
