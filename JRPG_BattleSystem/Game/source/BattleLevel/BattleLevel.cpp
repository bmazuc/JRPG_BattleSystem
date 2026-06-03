#include "BattleLevel/BattleLevel.h"
#include "BattleLevel/Spawners/EnemySpawner.h"
#include "BattleLevel/Spawners/PlayerSpawner.h"
#include "Components/Camera/CameraComponent.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Common/UI/LoadLevelButton.h"
#include "UI/Text.h"
#include "Core/Resource/ResourceManager.h"
#include "Rendering/Material.h"
#include "BattleLevel/BattleManager.h"
#include "World/World.h"
#include "World/Systems/UISystem.h"
#include "UI/UserWidget.h"

void BattleLevel::LoadAssets()
{
	ResourceManager::LoadPNGTexture("Assets/goblin.png", "goblin");
	ResourceManager::LoadPNGTexture("Assets/battleback1_0.png", "background");
}

void BattleLevel::CreateLevel()
{
	BattleManager* battleManager = AddSubsystem<BattleManager>("battleManager");

	Scene* scene = GetScene();

	EnemySpawner* enemySpawner = scene->SpawnActor<EnemySpawner>("EnemySpawner", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(100, 240)));
	enemySpawner->AddCharacterData(CharacterData("goblin", "default", glm::vec3(1, 0, 0), glm::vec2(80, 83))); // Red enemy
	enemySpawner->AddCharacterData(CharacterData("goblin", "default", glm::vec3(0, 1, 0), glm::vec2(80, 83))); // Green enemy
	enemySpawner->AddCharacterData(CharacterData("goblin", "default", glm::vec3(0, 0, 1), glm::vec2(80, 83))); // Blue enemy
	battleManager->SetEnemySpawner(enemySpawner);

	PlayerSpawner* playerSpawner = scene->SpawnActor<PlayerSpawner>("EnemySpawner", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(540, 240)));
	playerSpawner->AddCharacterData(CharacterData("goblin", "default", glm::vec3(1, 1, 0), glm::vec2(80, 83)));
	playerSpawner->AddCharacterData(CharacterData("goblin", "default", glm::vec3(1, 0, 1), glm::vec2(80, 83)));
	playerSpawner->AddCharacterData(CharacterData("goblin", "default", glm::vec3(0, 1, 1), glm::vec2(80, 83)));
	battleManager->SetPlayerSpawner(playerSpawner);

	Actor* background = scene->SpawnActor<Actor>("Background", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 240)));
	SpriteRendererComponent* backgroundSpriteRenderer = background->SpawnSceneComponent<SpriteRendererComponent>("Sprite renderer", SceneComponentSpawnInfo(), "background");
	backgroundSpriteRenderer->SetSize(glm::vec2(640, 480));

	Actor* cameraObject = scene->SpawnActor<Actor>("MainCamera", ActorSpawnInfo());
	CameraComponent* camera = cameraObject->SpawnSceneComponent<CameraComponent>("Camera component", SceneComponentSpawnInfo());
	scene->SetActiveCamera(camera);

	UISystem* uiSystem = world->GetUISystem();

	UserWidget* userWidget = uiSystem->CreateUserWidget<UserWidget>("UserWidget", UISpawnInfo());

	LoadLevelButton* mainMenuButton = userWidget->CreateWidget<LoadLevelButton>("MainMenuButton", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 390)));
	mainMenuButton->GetMaterial()->SetTexture("button");
	mainMenuButton->SetSize(glm::vec2(150, 50));
	mainMenuButton->SetLevelToLoad("mainMenu");

	Text* mainMenuButtonText = userWidget->CreateWidget<Text>("MainMenuButtonText", UISpawnInfo(mainMenuButton, TransformSpace::Local));
	mainMenuButtonText->SetContent("Main Menu");
	mainMenuButtonText->SetSize(24);

	Text* turnText = userWidget->CreateWidget<Text>("TurnText", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(100, 20)));
	turnText->SetSize(24);
	battleManager->SetTurnText(turnText);
}