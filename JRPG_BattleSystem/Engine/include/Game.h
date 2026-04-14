#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "Scene.h"

// A virtual class needed to be inherited to implement game logic
class Game
{
public:
	Game();
	~Game();

	virtual void Init() = 0;
	virtual void Update() = 0;

	Scene* GetScene() const { return scene; }

protected:
	Scene* scene;
};

#endif // __GAME_H_INCLUDED__