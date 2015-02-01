#include <memory>

#include "Arc_Assert.hpp"
#include "B2_Helper.hpp"
#include "Box2D/Dynamics/Joints/b2PrismaticJoint.h"
#include "Level.hpp"
#include "LevelEntries.hpp"

using namespace std;
using namespace FluidGame;

const float GRAVITY_SCALE = 1.0f;
const float DENSITY = 1.0f;
const float WORLD_MARGIN = 10.0f;
const float SIZE_OF_WORLD_MARGIN = 1.0f;
const int MAX_PARTICLES = 0;
const float WOOD_PLATFORM_SIZE = 0.3f;
const float WOOD_DENSITY = 0.5f;

WorldPtr MakeWorld()
{
	return make_unique<b2World>(b2Vec2{ 0.0f, 9.81f });
}

b2Body* CreateWoodPlatform(WorldPtr world, b2Body* anchor, float width, float x, float y)
{
	const float TAIL_SIZE = 0.7f;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { x, y };
	auto body = world->CreateBody(&bodyDef);

	auto l = (width - 2.0f * TAIL_SIZE) / 2.0f;
	
	b2PolygonShape shape;
	const b2Vec2 vertices[7] =
	{
		{ 0.0f, 0.0f },
		{ width, 0.0f },
		{ width, WOOD_PLATFORM_SIZE },
		{ l + 2.0f * TAIL_SIZE, WOOD_PLATFORM_SIZE },
		{ l + TAIL_SIZE, WOOD_PLATFORM_SIZE + TAIL_SIZE },
		{ l, WOOD_PLATFORM_SIZE },
		{ 0, WOOD_PLATFORM_SIZE }
	};
	shape.Set(vertices, 7);

	auto fixture = body->CreateFixture(&shape, WOOD_DENSITY);

	auto seperation = x - anchor->GetPosition().x;
	
	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = body;
	prismaticJointDef.bodyB = anchor;
	prismaticJointDef.localAxisA = { 0.0f, 1.0f };
	prismaticJointDef.collideConnected = true;
	prismaticJointDef.localAnchorA = { -seperation, 0.0f };
	world->CreateJoint(&prismaticJointDef);

	return body;
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
	b2ParticleSystem *particleSystem = world.get()->CreateParticleSystem(&particleSystemDef);

	particleSystem->SetGravityScale(GRAVITY_SCALE);
	particleSystem->SetDensity(DENSITY);
	particleSystem->SetStrictContactCheck(true);

	auto leftBlock = CreateStaticBox(1.0f, 8.0f, 3.0f, 7.0f, *world);
	CreateStaticBox(13.0f, 8.0f, 3.0f, 7.0f, *world);
	CreateStaticBox(1.0f, 14.0f, 16.0, 1.0f, *world);

	//auto emitter = CreateEmitter(12.0f, 9.0f, particleSystem);
	CreateWoodPlatform(world, leftBlock, 3.0f, 7.0f, 10.0f);

	// TODO::JT create a player and start/end points

	auto result = make_shared<Level>(world, particleSystem);
	//result->GetMutableEmitters().push_back(emitter);

	result->SetKillBoxes(CreateKillBox(world));

	auto character = make_shared<Character>(b2Vec2{ 1.5f, 5.0f }, world.get());
	result->SetMainCharacter(character);


	return result;
}