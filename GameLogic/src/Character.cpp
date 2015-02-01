#include "Character.hpp"

const float MOVE_SPEED = 6.0f;
const float JUMP_SPEED = 16.0f;

const float CHAR_WIDTH = 0.3f;
const float CHAR_HEIGHT = 0.7f;

const float GRAVITY_SCALE = 4.25f;
const float FRICTION = 1.5f;

FluidGame::Character::Character(b2Vec2 position, WorldPtr world)
{
	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	bodyDef.gravityScale = GRAVITY_SCALE;
	bodyDef.position = { position.x, position.y };
	auto body = world->CreateBody(&bodyDef);

	auto shape = CreateBoxShape(CHAR_WIDTH, CHAR_HEIGHT);
	auto fixture = body->CreateFixture(&shape, 1.0f);
	fixture->SetFriction(FRICTION);
	
	m_Body = WrapB2Resource(world.get(), body);
}

void FluidGame::Character::Jump()
{
	auto currentVelocity = m_Body->GetLinearVelocity();
	m_Body->SetLinearVelocity({ currentVelocity.x, -JUMP_SPEED });
}

void FluidGame::Character::MoveRight()
{
	auto currentVelocity = m_Body->GetLinearVelocity();
	m_Body->SetLinearVelocity({ MOVE_SPEED, currentVelocity.y });
}

void FluidGame::Character::MoveLeft()
{
	auto currentVelocity = m_Body->GetLinearVelocity();
	m_Body->SetLinearVelocity({ -MOVE_SPEED, currentVelocity.y });
}

