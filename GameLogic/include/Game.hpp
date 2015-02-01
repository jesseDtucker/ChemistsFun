#pragma once

#include <future>
#include <memory>

#include "B2_Helper.hpp"
#include "PropertyHelper.hpp"
 
namespace FluidGame
{
	class Emitter;

	class Game : public b2DestructionListener
	{
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		PROP_GET(bool, IsRunning);

		std::pair<int, b2Vec2*> GetParticlesPositions();
		PROP_GET(BodyPtr, Ground);

		void HackSetup();
		void RunSim();
		

		// Listeners
		virtual void SayGoodbye(b2Joint* joint) override;
		virtual void SayGoodbye(b2Fixture* fixture) override;
		virtual void SayGoodbye(b2ParticleGroup* group) override;
		virtual void SayGoodbye(b2ParticleSystem* particleSystem, int32 index) override;
		

	private:
		WorldPtr m_world;
		ParticleSystemPtr m_particleSystem;
		std::mutex m_syncLock;
		std::shared_ptr<Emitter> m_emitter;
	};
}