#include <memory>

#include "B2_Helper.hpp"
#include "Level.hpp"
#include "LevelEntries.hpp"

using namespace std;
using namespace FluidGame;

const float GRAVITY_SCALE = 1.0f;
const float DENSITY = 1.0f;
const int MAX_PARTICLES = 500;

void CreateStaticBox(float x, float y, float width, float height, b2World& world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = { x, y };
	auto body = world.CreateBody(&bodyDef);

	b2PolygonShape shape;
	const b2Vec2 vertices[4] = 
	{
		{0, 0},
		{0, 0 + height},
		{0 + width, 0 + height},
		{0 + width, 0}
	};
	shape.Set(vertices, 4);
	body->CreateFixture(&shape, 0.0f);
}

Emitter CreateEmitter(float x, float y, ParticleSystemPtr particleSystem)
{
	return { particleSystem.get(), {x, y} };
}

WorldPtr MakeWorld()
{
	return make_unique<b2World>(b2Vec2{ 0.0f, 9.81f });
}

std::shared_ptr<Level> LevelEntries::LoadLevelOne(float particleRadius)
{
	WorldPtr world = MakeWorld();
	b2ParticleSystemDef particleSystemDef;
	particleSystemDef.radius = particleRadius;
	particleSystemDef.maxCount = MAX_PARTICLES;
	ParticleSystemPtr particleSystem = WrapB2Resource(world.get(), world->CreateParticleSystem(&particleSystemDef));

	particleSystem->SetGravityScale(GRAVITY_SCALE);
	particleSystem->SetDensity(DENSITY);
	particleSystem->SetStrictContactCheck(true);

	CreateStaticBox(1.0f, 8.0f, 3.0f, 7.0f, *world);
	CreateStaticBox(13.0f, 8.0f, 3.0f, 7.0f, *world);
	CreateStaticBox(1.0f, 14.0f, 16.0, 1.0f, *world);

	auto emitter = CreateEmitter(8.0f, 3.0f, particleSystem);

	// TODO::JT create a player and start/end points

	auto result = make_shared<Level>(world, particleSystem);
	result->GetMutableEmitters().push_back(emitter);

	return result;
}