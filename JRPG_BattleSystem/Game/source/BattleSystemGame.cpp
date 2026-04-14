#include "BattleSystemGame.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

BattleSystemGame::~BattleSystemGame()
{
    delete sprite;
    sprite = nullptr;

    delete sprite2;
    sprite2 = nullptr;
}

void BattleSystemGame::Init(SpriteRenderer* renderer)
{
    sprite = new Sprite();
    sprite->LoadPNG("Assets/battleback1_0.png");
    sprite->SetPosition(glm::vec2(320, 240));
    sprite->SetSize(glm::vec2(640, 480));

    renderer->AddSprite(sprite);

    sprite2 = new Sprite();
    sprite2->LoadPNG("Assets/goblin.png");
    sprite2->SetPosition(glm::vec2(320, 240));
    sprite2->SetSize(glm::vec2(300, 306));

    renderer->AddSprite(sprite2);
}

void BattleSystemGame::Update()
{

}