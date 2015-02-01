#pragma once

#include <future>
#include <memory>

#include "B2_Helper.hpp"
#include "Level.hpp"
#include "PropertyHelper.hpp"
 
namespace FluidGame
{
	class Emitter;

	class Game
	{
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

		PROP_GET(bool, IsRunning);
		PROP_GET(Level, CurrentLevel);

		void RunSim(const Level& level);

	private:
	};
}