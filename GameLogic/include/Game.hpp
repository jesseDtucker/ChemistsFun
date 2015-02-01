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
		PROP_GET(std::shared_ptr<Level>, CurrentLevel);

		void RunSim(std::shared_ptr<Level> level);

	private:
	};
}