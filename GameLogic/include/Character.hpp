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
		void MoveLeft();
		void MoveRight();
		void Jump();
	private:
	};
}