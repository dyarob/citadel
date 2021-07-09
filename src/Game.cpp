#include "Game.hpp"

Game::Game() {
	std::ifstream fsave("save");
	if (fsave.is_open())
		getline(fsave, room);
	else room = "entry";
	fsave.close();
}
