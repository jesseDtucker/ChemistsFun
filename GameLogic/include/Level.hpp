#pragma once

#include "B2_Helper.hpp"
#include "Character.hpp"
#include "LevelEntries.hpp"
#include "PropertyHelper.hpp"

namespace FluidGame
{
	enum class MaterialType { WATER, ROCK, ERASER };
	class Level
	{
	public:

		Level(WorldPtr world, b2ParticleSystem* particleSystem);

		PROP_GET(WorldPtr, World);
		b2ParticleSystem* GetParticleSystem();
		PROP_SET_AND_GET(std::vector<std::shared_ptr<Emitter>>, Emitters);
		PROP_SET_AND_GET(std::vector<std::pair<b2Transform COMMA b2PolygonShape>>, KillBoxes);
		PROP_SET_AND_GET(std::shared_ptr<Character>, MainCharacter);
		PROP_SET_AND_GET(MaterialType, Material);
		PROP_SET_AND_GET(bool, DrawingMode);
		// TODO::JT add character???

		std::shared_ptr<Emitter> CreateEmitter(float x, float y);

		void Step(float dt);

	private:
		b2ParticleSystem* m_particleSystem;
		friend class LevelEntries;
	};
}