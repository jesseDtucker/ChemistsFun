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

std::shared_ptr<Emitter> FluidGame::CreateEmitter(float x, float y, ParticleSystemPtr particleSystem)
{
	return make_shared<Emitter>(particleSystem.get(), b2Vec2{ x, y });
}
