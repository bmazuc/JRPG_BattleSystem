#include "BattleLevel/BattleLevel.h"
#include "BattleLevel/EnemySpawner.h"
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
#include "BattleLevel/SwitchZOrderButton.h"

void BattleLevel::LoadAssets()
{
	ResourceManager::LoadPNGTexture("Assets/goblin.png", "goblin");
	ResourceManager::LoadPNGTexture("Assets/battleback1_0.png", "background");
}

void BattleLevel::CreateLevel()
{
	BattleManager* battleManager = AddSubsystem<BattleManager>("battleManager");

	Scene* scene = GetScene();

	EnemySpawner* spawner = scene->SpawnActor<EnemySpawner>("EnemySpawner", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(100, 240)));
	battleManager->SetEnemySpawner(spawner);

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

	Image* image1 = userWidget->CreateWidget<Image>("Image1", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(10, 390)), "goblin");
	image1->SetSize(glm::vec2(75, 77));

	Image* image2 = userWidget->CreateWidget<Image>("Image2", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(10, 390)));
	image2->SetSize(glm::vec2(75, 77));

	SwitchZOrderButton* switchButton = userWidget->CreateWidget<SwitchZOrderButton>("MainMenuButton", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(480, 390)));
	switchButton->GetMaterial()->SetTexture("button");
	switchButton->SetSize(glm::vec2(150, 50));
	switchButton->SetWidget(image1);

	Text* switchButtonText = userWidget->CreateWidget<Text>("SwitchButtonText", UISpawnInfo(switchButton, TransformSpace::Local));
	switchButtonText->SetContent("zOrder");
	switchButtonText->SetSize(24);
}