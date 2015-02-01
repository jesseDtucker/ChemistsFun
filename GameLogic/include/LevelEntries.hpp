#pragma once

#include <vector>

#include "Box2D/Box2D.h"
#include "Emitter.hpp"
#include "PropertyHelper.hpp"

namespace FluidGame
{
	class Level;

	class LevelEntries
	{
	public:
		static std::shared_ptr<Level> LoadLevelOne(float particleRadius);
	private:
	};
}