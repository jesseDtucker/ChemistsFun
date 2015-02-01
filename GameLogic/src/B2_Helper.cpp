#include <memory>

#include "B2_Helper.hpp"
#include "Emitter.hpp"

using namespace std;
using namespace FluidGame;

b2PolygonShape FluidGame::CreateBoxShape(float width, float height)
{
	b2PolygonShape shape;
	const b2Vec2 vertices[4] =
	{
		{ 0, 0 },
		{ 0, 0 + height },
		{ 0 + width, 0 + height },
		{ 0 + width, 0 }
	};
	shape.Set(vertices, 4);
	return shape;
}

b2Body* FluidGame::CreateStaticBox(float x, float y, float width, float height, b2World& world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = { x, y };
	auto body = world.CreateBody(&bodyDef);

	auto shape = CreateBoxShape(width, height);
	body->CreateFixture(&shape, 1.0f);
	return body;
}

std::shared_ptr<Emitter> FluidGame::CreateEmitter(float x, float y, b2ParticleSystem* particleSystem)
{
	return make_shared<Emitter>(particleSystem, b2Vec2{ x, y });
}

std::shared_ptr<Emitter> FluidGame::CreateJet(float x, float y, b2ParticleSystem* particleSystem, float lifetime, float strength)
{
	return make_shared<Emitter>(particleSystem, b2Vec2{ x, y }, strength, b2Vec2{ 0.001f, -40.0f }, b2Vec2{ 0.002f, -100.0f }, lifetime, 0.4f);
}
