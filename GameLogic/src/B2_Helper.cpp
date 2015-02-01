#include "B2_Helper.hpp"
#include "Emitter.hpp"

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
	body->CreateFixture(&shape, 0.0f);
	return body;
}

Emitter FluidGame::CreateEmitter(float x, float y, ParticleSystemPtr particleSystem)
{
	return{ particleSystem.get(), { x, y } };
}

FluidGame::ParticleSystemPtr FluidGame::WrapB2Resource(b2World* world, b2ParticleSystem* res)
{
	std::function<void(b2ParticleSystem*)> deleter = [world](b2ParticleSystem* p)
	{
		world->DestroyParticleSystem(p);
	};

	return ParticleSystemPtr(res, deleter);
}

FluidGame::BodyPtr FluidGame::WrapB2Resource(b2World* world, b2Body* body)
{
	std::function<void(b2Body*)> deleter = [world](b2Body* p)
	{
		world->DestroyBody(p);
	};

	return BodyPtr(body, deleter);
}
