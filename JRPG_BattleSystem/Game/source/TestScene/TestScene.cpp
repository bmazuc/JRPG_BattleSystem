#include "TestScene/TestScene.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "TestScene/MovingEntity.h"
#include "TestScene/RotatingEntity.h"
#include "Components/Camera/CameraComponent.h"
#include "Core/Resource/ResourceManager.h"
#include "UI/Text.h"
#include "Common/UI/LoadSceneButton.h"
#include "TestScene/CrossButton.h"
#include "Rendering/Material.h"
#include "TestScene/KillableEntity.h"

void TestScene::CreateScene()
{
    CreateUI();

    MovingEntity* enemy = SpawnActor<MovingEntity>("MovingEnemy", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 240)), "goblin");
    enemy->SetSpeed(50.0f);
    SpriteRendererComponent* enemySprite = enemy->GetSpriteRenderer();
    enemySprite->SetSize(glm::vec2(150, 153));
    enemySprite->SetZOrder(1);

    Actor* followEnemy = SpawnActor<Actor>("FollowEnemy", ActorSpawnInfo(enemy, TransformSpace::Local, glm::vec2(165, 0)));
    SpriteRendererComponent* followEnemySpriteRenderer = followEnemy->AddComponent<SpriteRendererComponent>("Sprite renderer", nullptr,
        glm::vec2(0, 0), 0, glm::vec2(1,1),
        "goblin");
    followEnemySpriteRenderer->SetSize(glm::vec2(150, 153));
    followEnemySpriteRenderer->SetZOrder(2);

    KillableEntity* followEnemy2 = SpawnActor<KillableEntity>("KillableEnemy", ActorSpawnInfo(enemy, TransformSpace::Local, glm::vec2(-165, 0)), "goblin");
    SpriteRendererComponent* followEnemySpriteRenderer2 = followEnemy2->GetSpriteRenderer();
    followEnemySpriteRenderer2->SetSize(glm::vec2(150, 153));
    followEnemySpriteRenderer2->SetZOrder(3);

    RotatingEntity* rotatingEnemy = SpawnActor<RotatingEntity>("RotatingEnemy", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(600, 400)), "goblin");
    rotatingEnemy->SetSpeed(50.0f);
    SpriteRendererComponent* rotatingEnemySprite = rotatingEnemy->GetSpriteRenderer();
    rotatingEnemySprite->SetSize(glm::vec2(75, 78));
    rotatingEnemySprite->SetZOrder(1);
    rotatingEnemySprite->GetMaterial()->SetColor(glm::vec3(1, 0, 0));

    Actor* cameraObject = SpawnActor<Actor>("MainCamera", ActorSpawnInfo());
    CameraComponent* camera = cameraObject->AddComponent<CameraComponent>("Camera component", nullptr,
        glm::vec2(0, 0), 0, glm::vec2(1, 1));
    SetActiveCamera(camera);

    Actor* background = SpawnActor<Actor>("Background", ActorSpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 240)));
    SpriteRendererComponent* backgroundSpriteRenderer = background->AddComponent<SpriteRendererComponent>("Sprite renderer", nullptr,
        glm::vec2(0, 0), 0, glm::vec2(1, 1),
        "background");
    backgroundSpriteRenderer->SetSize(glm::vec2(640, 480));
}

void TestScene::LoadAssets()
{
}

void TestScene::CreateUI()
{
    Text* goblinText = CreateUIElement<Text>("GoblinText", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 50)));
    goblinText->SetContent("Click on the middle goblin to make them move or stop.");
    goblinText->SetColor(glm::vec3(1, 0, 0));
    goblinText->SetSize(24);

    Text* goblinText2 = CreateUIElement<Text>("GoblinText2", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 75)));
    goblinText2->SetContent("Click on the red goblin to make him rotate or stop.");
    goblinText2->SetColor(glm::vec3(1, 0, 0));
    goblinText2->SetSize(24);

    Text* crossText = CreateUIElement<Text>("CrossText", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 100)));
    crossText->SetContent("Click on the cross to destroy its button.");
    crossText->SetColor(glm::vec3(1, 0, 0));
    crossText->SetSize(24);

    LoadSceneButton* mainMenuButton = CreateUIElement<LoadSceneButton>("MainMenuButton", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 390)));
    mainMenuButton->GetMaterial()->SetTexture("button");
    mainMenuButton->SetSize(glm::vec2(150, 50));
    mainMenuButton->SetSceneToLoad("mainMenu");

    Text* mainMenuButtonText = CreateUIElement<Text>("MainMenuButtonText", UISpawnInfo(mainMenuButton, TransformSpace::Local));
    mainMenuButtonText->SetContent("Main Menu");
    mainMenuButtonText->SetSize(24);

    CrossButton* crossButton = CreateUIElement<CrossButton>("CrossButton", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(40, 440)));
    crossButton->GetMaterial()->SetTexture("button");
    crossButton->SetSize(glm::vec2(30, 30));

    Text* crossButtonText = CreateUIElement<Text>("CrossButtonText", UISpawnInfo(crossButton, TransformSpace::Local));
    crossButtonText->SetContent("X");
    crossButtonText->SetSize(24);
}