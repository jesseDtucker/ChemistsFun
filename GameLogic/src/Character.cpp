#include "Character.hpp"

const float MOVE_SPEED = 6.0f;
const float JUMP_SPEED = 16.0f;

const float CHAR_WIDTH = 0.5f;
const float CHAR_HEIGHT = 1.2f;

const float GRAVITY_SCALE = 3.25f;
const float FRICTION = 1.5f;
const int MAX_JUMPS = 1; // character can jump twice, ie. double jump

FluidGame::Character::Character(b2Vec2 position, b2World* world)
	: m_jumpsLeft(MAX_JUMPS)
	, m_startPos(position)
{
	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	bodyDef.gravityScale = GRAVITY_SCALE;
	bodyDef.position = { position.x, position.y };

	//todo: add body to current level and draw in level->world
	m_body = world->CreateBody(&bodyDef);

	auto shape = CreateBoxShape(CHAR_WIDTH, CHAR_HEIGHT);
	auto fixture = m_body->CreateFixture(&shape, 1.0f);
	fixture->SetDensity(0.5);
	fixture->SetFriction(FRICTION);
}

void FluidGame::Character::Step(float dt)
{
	auto contactList = m_body->GetContactList();
	m_jumpsLeft = contactList != nullptr ? MAX_JUMPS : m_jumpsLeft;

}

void FluidGame::Character::Jump()
{
	if (m_jumpsLeft > 0)
	{
		auto currentVelocity = m_body->GetLinearVelocity();
		m_body->SetLinearVelocity({ currentVelocity.x, -JUMP_SPEED });
		--m_jumpsLeft;
	}
}

void FluidGame::Character::MoveRight()
{
	auto currentVelocity = m_body->GetLinearVelocity();
	m_body->SetLinearVelocity({ MOVE_SPEED, currentVelocity.y });
}

void FluidGame::Character::MoveLeft()
{
	auto currentVelocity = m_body->GetLinearVelocity();
	m_body->SetLinearVelocity({ -MOVE_SPEED, currentVelocity.y });
}

void FluidGame::Character::Kill()
{
	// on death just return the character to their start position
	m_body->SetTransform(m_startPos, m_body->GetAngle());
	m_body->SetLinearVelocity({ 0.0f, 0.0f });
}

b2Body* FluidGame::Character::GetBody()
{
	return m_body;
}

