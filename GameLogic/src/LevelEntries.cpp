#include <memory>

#include "Arc_Assert.hpp"
#include "B2_Helper.hpp"
#include "Level.hpp"
#include "LevelEntries.hpp"

using namespace std;
using namespace FluidGame;

const float GRAVITY_SCALE = 1.0f;
const float DENSITY = 1.0f;
const float WORLD_MARGIN = 10.0f;
const float SIZE_OF_WORLD_MARGIN = 1.0f;
const int MAX_PARTICLES = 0;

WorldPtr MakeWorld()
{
	return make_unique<b2World>(b2Vec2{ 0.0f, 9.81f });
}

std::vector<std::pair<b2Transform, b2PolygonShape>> CreateKillBox(WorldPtr world)
{
	b2AABB worldAABB;
	worldAABB.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	worldAABB.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);

	auto body = world->GetBodyList();
	while (body != nullptr)
	{
		b2AABB bodyAABB;
		bodyAABB.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
		bodyAABB.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);
		b2Fixture* fixture = body->GetFixtureList();
		while (fixture != NULL)
		{
			bodyAABB.Combine(bodyAABB, fixture->GetAABB(0));
			fixture = fixture->GetNext();
		}

		body = body->GetNext();
		worldAABB.Combine(worldAABB, bodyAABB);
	}

	auto topLeft = worldAABB.lowerBound;
	auto bottomRight = worldAABB.upperBound;

	topLeft.x -= WORLD_MARGIN + SIZE_OF_WORLD_MARGIN;
	topLeft.y -= WORLD_MARGIN + SIZE_OF_WORLD_MARGIN;
	bottomRight.x += WORLD_MARGIN;
	bottomRight.y += WORLD_MARGIN;

	auto height = bottomRight.y - topLeft.y;
	auto width = bottomRight.x - topLeft.x;

	b2Transform leftTransform(b2Vec2{ topLeft.x, topLeft.y }, b2Rot(0.0f));
	b2Transform topTransform(b2Vec2{ topLeft.x, topLeft.y }, b2Rot(0.0f));
	b2Transform rightTransform(b2Vec2{ topLeft.x + width, topLeft.y }, b2Rot(0.0f));
	b2Transform bottomTransform(b2Vec2{ topLeft.x, topLeft.y + height }, b2Rot(0.0f));

	return
	{
		{ leftTransform, CreateBoxShape(SIZE_OF_WORLD_MARGIN, height + SIZE_OF_WORLD_MARGIN) }, // left
		{ topTransform, CreateBoxShape(width + SIZE_OF_WORLD_MARGIN, SIZE_OF_WORLD_MARGIN) }, // top
		{ bottomTransform, CreateBoxShape(width + SIZE_OF_WORLD_MARGIN, SIZE_OF_WORLD_MARGIN) }, // bottom
		{ rightTransform, CreateBoxShape(SIZE_OF_WORLD_MARGIN, height + SIZE_OF_WORLD_MARGIN) }, // right
	};
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
	result->SetKillBoxes(CreateKillBox(world));

	result->SetMainCharacter(make_shared<Character>(b2Vec2{ 1.5f, 5.0f }, world));


	return result;
}