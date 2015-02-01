#pragma once

#include "B2_Helper.hpp"
#include "Character.hpp"
#include "LevelEntries.hpp"
#include "PropertyHelper.hpp"

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
		PROP_SET_AND_GET(std::shared_ptr<Character>, MainCharacter);
		// TODO::JT add character???
		
		bool emitterPresent;
		float emitterX;
		float emitterY;

		void EmitterPos(float x, float y) { emitterX = x; emitterY = y; }
		void EmitterOn() { emitterPresent = true; }
		void EmitterOff() { emitterPresent = false; }

		void Step(float dt);

	private:

		friend class LevelEntries;
	};
}