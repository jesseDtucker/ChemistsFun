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
		// TODO::JT add character???

		void Step(float dt);

	private:

		friend class LevelEntries;
	};
}