#include "Core/Game.h"

Game::Game()
{
	scene = new Scene();
}

void Game::Init()
{
	if (scene)
	{
		scene->Init();
	}
}

void Game::Update()
{
	if (scene)
	{
		scene->Update();
	}
}

Game::~Game()
{
	delete scene;
	scene = nullptr;
}