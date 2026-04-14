#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

class SpriteRenderer;

// A virtual class needed to be inherited to implement game logic
class Game
{
public:
	// SpriteRenderer is temporary. I need to find a better way to register sprite to render.
	virtual void Init(SpriteRenderer* renderer) = 0;
	virtual void Update() = 0;
};

#endif // __GAME_H_INCLUDED__