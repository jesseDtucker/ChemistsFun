#include <chrono>
#include <future>

#include "Arc_Assert.hpp"
#include "Box2D/Box2D.h"
#include "Emitter.hpp"
#include "Game.hpp"

using namespace std;
using namespace FluidGame;

const float STEP_SIZE = 1.0f / 60.0f;

const float WIDTH = 10.0f;
const float HEIGHT = 10.0f;
const float EDGE_WIDTH = 0.5f;

Game::Game()
	: m_CurrentLevel(nullptr)
{

}

void CreateBounds(b2Body& ground)
{
	{
		b2PolygonShape shape;
		// left edge
		const b2Vec2 vertices[4] = {
			b2Vec2(1.0f-EDGE_WIDTH, 1.0f),
			b2Vec2(1.0f, 1.0),
			b2Vec2(1.0f, HEIGHT),
			b2Vec2(1.0f-EDGE_WIDTH, HEIGHT) };
		shape.Set(vertices, 4);
		ground.CreateFixture(&shape, 0.0f);
	}

	{
		b2PolygonShape shape;
		const b2Vec2 vertices[4] = {
			b2Vec2(0, HEIGHT),
			b2Vec2(WIDTH, HEIGHT),
			b2Vec2(WIDTH, HEIGHT + EDGE_WIDTH),
			b2Vec2(1.0f, HEIGHT + EDGE_WIDTH) };
		shape.Set(vertices, 4);
		ground.CreateFixture(&shape, 0.0f);
	}

	{
		b2PolygonShape shape;
		const b2Vec2 vertices[4] = {
			b2Vec2(WIDTH, 1.0f),
			b2Vec2(WIDTH + EDGE_WIDTH, 1.0),
			b2Vec2(WIDTH + EDGE_WIDTH, HEIGHT),
			b2Vec2(WIDTH, HEIGHT) };
		shape.Set(vertices, 4);
		ground.CreateFixture(&shape, 0.0f);
	}
}

void Game::RunSim(std::shared_ptr<Level> level)
{
	m_CurrentLevel = level;
	m_IsRunning = true;
	async([this]()
	{
		while (m_IsRunning)
		{
			auto stepSize = chrono::milliseconds((int) (STEP_SIZE * 1000.0f));
			auto startTime = chrono::system_clock::now();

			m_CurrentLevel->Step(STEP_SIZE);

			auto timeTaken = chrono::system_clock::now() - startTime;
			if (timeTaken < stepSize)
			{
				this_thread::sleep_for((stepSize - timeTaken) / 4);
			}
		}
	});
}