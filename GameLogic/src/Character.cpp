#include "Character.hpp"

const float MOVE_SPEED = 4.0f;
const float JUMP_SPEED = 9.0f;

const float CHAR_WIDTH = 0.5f;
const float CHAR_HEIGHT = 1.5f;

FluidGame::Character::Character(b2Vec2 position, WorldPtr world)
{
	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { position.x, position.y };
	auto body = world->CreateBody(&bodyDef);

	auto shape = CreateBoxShape(CHAR_WIDTH, CHAR_HEIGHT);
	body->CreateFixture(&shape, 1.0f);
	
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

