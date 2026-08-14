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
#include "BattleLevel/UI/BattleWidget.h"
#include "BattleLevel/UI/CountdownWidget.h"
#include "BattleLevel/UI/GameOverWidget.h"
#include "BattleLevel/Characters/PlayerCharacter.h"

#include "BattleLevel/Abilities/AllOrNothingAbility.h"
#include "BattleLevel/Abilities/SpellAbility.h"
#include "BattleLevel/Abilities/RegenerateAbility.h"

#include "Rendering/Color.h"

void BattleLevel::LoadAssets()
{
	ResourceManager::LoadPNGTexture("Assets/goblin.png", "goblin");
	ResourceManager::LoadPNGTexture("Assets/goblin2.png", "goblin2");
	ResourceManager::LoadPNGTexture("Assets/Fighter.png", "warrior");
	ResourceManager::LoadPNGTexture("Assets/Wizard.png", "wizard");
	ResourceManager::LoadPNGTexture("Assets/Cleric.png", "cleric");
	ResourceManager::LoadPNGTexture("Assets/battleback1_0.png", "background");
}

void BattleLevel::CreateLevel()
{
	BattleManager* battleManager = CreateBattleManager();
	battleManager->SetPlayerController(playerController);
	Scene* scene = GetScene();

	EnemySpawner* enemySpawner = scene->SpawnActor<EnemySpawner>("EnemySpawner", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(100, 160)));
	enemySpawner->AddCharacterData(CharacterData("", "goblin", "default", Colors::White, glm::vec2(80, 83), 
		CharacterAttributes(60, 0, 30, 10, 0, 0)));
	enemySpawner->AddCharacterData(CharacterData("", "goblin2", "default", Colors::White, glm::vec2(80, 83),
		CharacterAttributes(40, 0, 45, 10, 0, 0)));
	battleManager->SetEnemySpawner(enemySpawner);

	PlayerSpawner* playerSpawner = scene->SpawnActor<PlayerSpawner>("EnemySpawner", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(540, 160)));
	playerSpawner->AddCharacterData(PlayerCharacterData("Warrior", "warrior", "default", Colors::White, glm::vec2(80, 83),
		CharacterAttributes(100, 100, 30, 20, 0, 0), new AllOrNothingAbility(20)));
	playerSpawner->AddCharacterData(PlayerCharacterData("Wizard", "wizard", "default", Colors::White, glm::vec2(80, 83),
		CharacterAttributes(100, 100, 20, 10, 40, 0), new SpellAbility(10)));
	playerSpawner->AddCharacterData(PlayerCharacterData("Cleric", "cleric", "default", Colors::White, glm::vec2(80, 83),
		CharacterAttributes(100, 100, 20, 15, 0, 0), new RegenerateAbility(10)));
	battleManager->SetPlayerSpawner(playerSpawner);

	Actor* background = scene->SpawnActor<Actor>("Background", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 240)));
	SpriteRendererComponent* backgroundSpriteRenderer = background->SpawnSceneComponent<SpriteRendererComponent>("Sprite renderer", SceneComponentSpawnInfo(), "background");
	backgroundSpriteRenderer->SetSize(glm::vec2(640, 480));

	Actor* cameraObject = scene->SpawnActor<Actor>("MainCamera", ActorSpawnInfo());
	CameraComponent* camera = cameraObject->SpawnSceneComponent<CameraComponent>("Camera component", SceneComponentSpawnInfo());
	scene->SetActiveCamera(camera);

	UISystem* uiSystem = world->GetUISystem();

	CreateBattleUI(battleManager, uiSystem);
}

BattleManager* BattleLevel::CreateBattleManager()
{
	BattleConfig battleConfig;
	battleConfig.enemyTurnDuration = 0.5f;
	battleConfig.blinkDuration = 0.2f;
	battleConfig.damageTextDuration = 1.0f;
	battleConfig.damageTextSpeed = 30.0f;

	BattleManager* battleManager = AddSubsystem<BattleManager>("battleManager");
	battleManager->SetBattleConfig(battleConfig);
	return battleManager;
}

void BattleLevel::CreateBattleUI(BattleManager* battleManager, UISystem* uiSystem)
{
	BattleWidget* battleWidget = uiSystem->CreateUserWidget<BattleWidget>("BattleWidget", UISpawnInfo());
	battleWidget->SetCurrentScene(GetScene());
	battleWidget->SetInfosBackgroundTexture("button");
	battleManager->SetBattleWidget(battleWidget);

	CountdownWidget* countdownWidget = uiSystem->CreateUserWidget<CountdownWidget>("CountdownWidget", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 240)));
	battleManager->SetCountdownWidget(countdownWidget);

	GameOverWidget* gameOverWidget = uiSystem->CreateUserWidget<GameOverWidget>("GameOverWidget", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 240)));
	battleManager->SetGameOverwidget(gameOverWidget);
}