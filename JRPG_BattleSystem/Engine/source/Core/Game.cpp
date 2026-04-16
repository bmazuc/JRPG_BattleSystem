#include "Core/Game.h"

Game::Game()
{
	scene = new Scene();
}

Game::~Game()
{
	delete scene;
	scene = nullptr;
}