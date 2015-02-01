#include "Character.hpp"

const float MOVE_SPEED = 6.0f;
const float JUMP_SPEED = 16.0f;

const float CHAR_WIDTH = 0.3f;
const float CHAR_HEIGHT = 0.7f;

const float GRAVITY_SCALE = 4.25f;
const float FRICTION = 1.5f;
const int MAX_JUMPS = 1; // character can jump twice, ie. double jump

FluidGame::Character::Character(b2Vec2 position, WorldPtr world)
	: m_jumpsLeft(MAX_JUMPS)
	, m_startPos(position)
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

void FluidGame::Character::Step(float dt)
{
	auto contactList = m_Body->GetContactList();
	m_jumpsLeft = contactList != nullptr ? MAX_JUMPS : m_jumpsLeft;

}

void FluidGame::Character::Jump()
{
	if (m_jumpsLeft > 0)
	{
		auto currentVelocity = m_Body->GetLinearVelocity();
		m_Body->SetLinearVelocity({ currentVelocity.x, -JUMP_SPEED });
		--m_jumpsLeft;
	}
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

void FluidGame::Character::Kill()
{
	// on death just return the character to their start position
	m_Body->SetTransform(m_startPos, m_Body->GetAngle());
	m_Body->SetLinearVelocity({ 0.0f, 0.0f });
}

