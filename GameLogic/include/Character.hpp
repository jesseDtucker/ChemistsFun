#pragma once

#include "B2_Helper.hpp"
#include "PropertyHelper.hpp"

namespace FluidGame
{
	class Character
	{
	public:
		Character(b2Vec2 position, WorldPtr world);

		PROP_GET(BodyPtr, Body);
		void Step(float dt);
		void MoveLeft();
		void MoveRight();
		void Jump();
		void Kill();
	private:
		int m_jumpsLeft;
		b2Vec2 m_startPos;
	};
}