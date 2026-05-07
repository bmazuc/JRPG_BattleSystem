#include "BattleScene/BattleScene.h"
#include "BattleScene/EnemySpawner.h"
#include "Components/Camera/CameraComponent.h"
#include "Components/Rendering/SpriteRendererComponent.h"

void BattleScene::LoadAssets()
{

}

void BattleScene::CreateScene()
{
	Actor* followEnemy = SpawnActor<Actor>("FollowEnemy", glm::vec2(320, 240), 0, glm::vec2(1, 1));
	SpriteRendererComponent* followEnemySpriteRenderer = followEnemy->AddComponent<SpriteRendererComponent>("Sprite renderer", nullptr,
		glm::vec2(0, 0), 0, glm::vec2(1, 1),
		"goblin");
	followEnemySpriteRenderer->SetSize(glm::vec2(150, 153));
	followEnemySpriteRenderer->SetZOrder(0);

	EnemySpawner* spawner = SpawnActor<EnemySpawner>("EnemySpawner", glm::vec2(320, 240), 0, glm::vec2(1, 1));

	EnemyData redEnemy;
	redEnemy.textureName = "goblin";
	redEnemy.spriteSize = glm::vec2(150, 153);
	redEnemy.color = glm::vec3(1, 0, 0);
	spawner->AddEnemyData(redEnemy);

	EnemyData blueEnemy;
	blueEnemy.textureName = "goblin";
	blueEnemy.spriteSize = glm::vec2(150, 153);
	blueEnemy.color = glm::vec3(0, 0, 1);
	spawner->AddEnemyData(blueEnemy);

	EnemyData greenEnemy;
	greenEnemy.textureName = "goblin";
	greenEnemy.spriteSize = glm::vec2(150, 153);
	greenEnemy.color = glm::vec3(0, 1, 0);
	spawner->AddEnemyData(greenEnemy);

	Actor* cameraObject = SpawnActor<Actor>("MainCamera", glm::vec2(0, 0), 0, glm::vec2(1, 1));
	CameraComponent* camera = cameraObject->AddComponent<CameraComponent>("Camera component", nullptr,
		glm::vec2(0, 0), 0, glm::vec2(1, 1));
	SetActiveCamera(camera);
}