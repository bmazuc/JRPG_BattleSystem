#include "BattleScene/BattleScene.h"
#include "BattleScene/EnemySpawner.h"
#include "Components/Camera/CameraComponent.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Common/UI/LoadSceneButton.h"
#include "UI/Text.h"
#include "Core/Resource/ResourceManager.h"
#include "Rendering/Material.h"

void BattleScene::LoadAssets()
{
	ResourceManager::LoadPNGTexture("Assets/goblin.png", "goblin");
	ResourceManager::LoadPNGTexture("Assets/battleback1_0.png", "background");
}

void BattleScene::CreateScene()
{
	EnemySpawner* spawner = SpawnActor<EnemySpawner>("EnemySpawner", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 240)));

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

	Actor* background = SpawnActor<Actor>("Background", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 240)));
	SpriteRendererComponent* backgroundSpriteRenderer = background->SpawnSceneComponent<SpriteRendererComponent>("Sprite renderer", SceneComponentSpawnInfo(), "background");
	backgroundSpriteRenderer->SetSize(glm::vec2(640, 480));

	Actor* cameraObject = SpawnActor<Actor>("MainCamera", ActorSpawnInfo());
	CameraComponent* camera = cameraObject->SpawnSceneComponent<CameraComponent>("Camera component", SceneComponentSpawnInfo());
	SetActiveCamera(camera);

	LoadSceneButton* mainMenuButton = CreateUIElement<LoadSceneButton>("MainMenuButton", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 390)));
	mainMenuButton->GetMaterial()->SetTexture("button");
	mainMenuButton->SetSize(glm::vec2(150, 50));
	mainMenuButton->SetSceneToLoad("mainMenu");

	Text* mainMenuButtonText = CreateUIElement<Text>("MainMenuButtonText", UISpawnInfo(mainMenuButton, TransformSpace::Local));
	mainMenuButtonText->SetContent("Main Menu");
	mainMenuButtonText->SetSize(24);
}