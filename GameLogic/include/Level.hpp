#pragma once

#include "B2_Helper.hpp"
#include "LevelEntries.hpp"

namespace FluidGame
{
	class Level
	{
	public:

		Level(WorldPtr world, ParticleSystemPtr particleSystem);

		PROP_GET(WorldPtr, World);
		PROP_GET(ParticleSystemPtr, ParticleSystem);
		PROP_SET_AND_GET(std::vector<Emitter>, Emitters);
		PROP_SET_AND_GET(std::vector<std::pair<b2Transform COMMA b2PolygonShape>>, KillBoxes);
		// TODO::JT add character???

		void Step(float dt);

	private:

		friend class LevelEntries;
	};
}