#include "BattleLevel/BattleManager.h"
#include "BattleLevel/Spawners/EnemySpawner.h"
#include "BattleLevel/Spawners/PlayerSpawner.h"
#include "Core/Random.h"
#include "BattleLevel/UI/BattleWidget.h"
#include "BattleLevel/UI/CountdownWidget.h"
#include "BattleLevel/UI/GameOverWidget.h"
#include "BattleLevel/UI/PlayerActionsMenu/PlayerActionsMenu.h"
#include "BattleLevel/Characters/PlayerCharacter.h"
#include "BattleLevel/Abilities/FleeAbility.h"
#include "BattleLevel/Abilities/AttackAbility.h"
#include "World/PlayerController.h"

void BattleManager::Initialize()
{
	currentState = BattleState::INIT;

	if (gameOverWidget)
	{
		gameOverWidget->SetVisible(false);
	}

	SpawnPlayerCharacters();
	SpawnEnemies();
	GenerateTurnOrder();

	if (!countdownWidget)
	{
		OnCountdownEnd();
	}
	else
	{
		currentState = BattleState::WAIT_FOR_COUNTDOWN_END;
	}
}

void BattleManager::Update(float deltaTime)
{
	// Enemy turn simulation
	if (currentState == BattleState::ENEMY_TURN)
	{
		currentEnemyTurnDuration -= deltaTime;
		if (currentEnemyTurnDuration <= 0.0f)
		{
			int index = Random::FromRange(0, (int)playerCharacters.size() - 1);
			if (Enemy* enemy = dynamic_cast<Enemy*>(currentCharacter))
			{
				currentState = BattleState::RESOLVING_TURN;
				waitingForBlinkEnd = true;
				waitingForDamageTextDestroy = true;

				AttackAbility* attackAbility = enemy->GetAttackAbility();
				attackAbility->SetTarget(playerCharacters[index]);
				attackAbility->Execute();
			}
		}
	}
}

void BattleManager::SetBattleWidget(BattleWidget* widget) 
{ 
	if (battleWidget == widget)
	{
		return;
	}

	if (battleWidget)
	{
		battleWidget->OnAllDamageTextDestroy.Unbind(OnAllDamageTextDestroyHandle);
		battleWidget->OnConstruct.Unbind(OnBattleWidgetConstructHandle);
	}

	battleWidget = widget; 

	if (battleWidget)
	{
		battleWidget->SetDamageTextDuration(battleConfig.damageTextDuration);
		battleWidget->SetDamageTextSpeed(battleConfig.damageTextSpeed);

		OnAllDamageTextDestroyHandle = battleWidget->OnAllDamageTextDestroy.Bind(this, &BattleManager::OnAllDamageTextDestroy);
		OnBattleWidgetConstructHandle = battleWidget->OnConstruct.Bind(this, &BattleManager::OnBattleWidgetConstruct);
	}
}

void BattleManager::SetCountdownWidget(CountdownWidget* widget)
{ 
	countdownWidget = widget; 
	if (countdownWidget)
	{
		countdownWidget->SetCount(battleConfig.count);
		countdownWidget->SetInBetweenCountDuration(battleConfig.inBetweenCountDuration);
		countdownWidget->OnCountdownEnd.Bind(this, &BattleManager::OnCountdownEnd);
	}
}

void BattleManager::SpawnPlayerCharacters()
{
	if (playerSpawner)
	{
		playerCharacters = playerSpawner->GeneratePlayerGroup();
		for (PlayerCharacter* playerCharacter : playerCharacters)
		{
			playerCharacter->SetBlinkDuration(battleConfig.blinkDuration);
			playerCharacter->OnSelected.Bind(this, &BattleManager::OnPlayerCharacterSelected);
			playerCharacter->OnDamageTaken.Bind(this, &BattleManager::OnCharacterTakeDamage);
			playerCharacter->OnBlinkEnd.Bind(this, &BattleManager::OnBlinkEnd);
			playerCharacter->OnDeath.Bind(this, &BattleManager::OnPlayerCharacterDeath);

			if (FleeAbility* fleeAbility = dynamic_cast<FleeAbility*>(playerCharacter->TryGetAbility("flee")))
			{
				fleeAbility->SetBattleManager(this);
			}
		}
	}
}

void BattleManager::SpawnEnemies()
{
	if (enemySpawner)
	{
		enemies = enemySpawner->GenerateEnemies();
		for (Enemy* enemy : enemies)
		{
			enemy->SetBlinkDuration(battleConfig.blinkDuration);

			enemy->OnSelected.Bind(this, &BattleManager::OnEnemySelected);
			enemy->OnDamageTaken.Bind(this, &BattleManager::OnCharacterTakeDamage);
			enemy->OnBlinkEnd.Bind(this, &BattleManager::OnBlinkEnd);
			enemy->OnDeath.Bind(this, &BattleManager::OnEnemyDeath);
		}
	}
}

void BattleManager::GenerateTurnOrder()
{
	turnOrder.clear();
	for (Character* playerCharacter : playerCharacters)
	{
		turnOrder.push_back(playerCharacter);
	}
	for (Enemy* enemy : enemies)
	{
		turnOrder.push_back(enemy);
	}

	Random::ShuffleVector(turnOrder);
}

void BattleManager::OnAllDamageTextDestroy()
{
	waitingForDamageTextDestroy = false;
	NextTurn();
}

void BattleManager::NextTurn()
{
	if (waitingForBlinkEnd || waitingForDamageTextDestroy)
	{
		return;
	}

	if (enemies.size() == 0)
	{
		SpawnEnemies();
		turnIndex = 0;
		GenerateTurnOrder();
	}
	else if (playerCharacters.size() == 0)
	{
		EndBattle();
		return;
	}

	currentAbilityWithActorTarget = nullptr;

	currentCharacter = turnOrder[turnIndex];

	if (dynamic_cast<Enemy*>(currentCharacter))
	{
		currentEnemyTurnDuration = battleConfig.enemyTurnDuration;
		currentState = BattleState::ENEMY_TURN;
		if (battleWidget)
		{
			battleWidget->HidePlayerActionsMenu();
			battleWidget->SetTurnText("Enemy Turn");
		}
	}
	else
	{
		currentState = BattleState::WAIT_FOR_ACTION_SELECTION;
		if (battleWidget)
		{
			battleWidget->ShowPlayerActionsMenu(dynamic_cast<PlayerCharacter*>(currentCharacter));
			battleWidget->SetTurnText(currentCharacter->GetName() + " Turn");
		}
	}

	turnIndex = (turnIndex + 1) % turnOrder.size();
}

void BattleManager::OnCharacterTakeDamage(Character* character, int damageTaken)
{
	if (battleWidget)
	{
		battleWidget->DisplayDamage(character->GetWorldPosition(), damageTaken);
	}
}

void BattleManager::OnPlayerCharacterDeath(Character* playerCharacter)
{
	turnOrder.erase(std::remove(turnOrder.begin(), turnOrder.end(), playerCharacter), turnOrder.end());

	if (turnIndex >= turnOrder.size())
	{
		turnIndex = 0;
	}

	playerCharacters.erase(std::remove(playerCharacters.begin(), playerCharacters.end(), playerCharacter), playerCharacters.end());
}

void BattleManager::OnEnemyDeath(Character* enemy)
{

	turnOrder.erase(std::remove(turnOrder.begin(), turnOrder.end(), enemy), turnOrder.end());

	if (turnIndex >= turnOrder.size())
	{
		turnIndex = 0;
	}

	enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());

	++killCount;
}

void BattleManager::OnBlinkEnd()
{
	waitingForBlinkEnd = false;
	NextTurn();
}

void BattleManager::OnPlayerCharacterSelected(Character* selectedCharacter)
{
	if (currentState == BattleState::WAIT_FOR_TARGET && currentAbilityWithActorTarget->GetTargetType() == TargetType::ALLY)
	{
		currentState = BattleState::RESOLVING_TURN;
		waitingForBlinkEnd = true;
		waitingForDamageTextDestroy = true;

		currentAbilityWithActorTarget->SetTarget(selectedCharacter);
		currentAbilityWithActorTarget->Execute();
	}
}

void BattleManager::OnEnemySelected(Character* selectedCharacter)
{
	if (currentState == BattleState::WAIT_FOR_TARGET && currentAbilityWithActorTarget->GetTargetType() == TargetType::ENEMY)
	{
		currentState = BattleState::RESOLVING_TURN;
		waitingForBlinkEnd = true;
		waitingForDamageTextDestroy = true;

		currentAbilityWithActorTarget->SetTarget(selectedCharacter);
		currentAbilityWithActorTarget->Execute();
	}
}

void BattleManager::InflictDamage(Character* attacker, Character* defender)
{
	currentState = BattleState::RESOLVING_TURN;
	waitingForBlinkEnd = true;
	waitingForDamageTextDestroy = true;

	int damages = std::max(0, attacker->GetAttributes().attack - defender->GetAttributes().defense);

	defender->TakeDamage(damages);
}

void BattleManager::OnCountdownEnd()
{
	countdownWidget = nullptr;
	NextTurn();
}

void BattleManager::EndBattle()
{
	currentState = BattleState::BATTLE_END;
	if (battleWidget)
	{
		battleWidget->SetTurnText("");
		battleWidget->HidePlayerActionsMenu();
	}

	if (gameOverWidget)
	{
		gameOverWidget->SetKillCount(killCount);
		gameOverWidget->SetVisible(true);
	}
}

void BattleManager::OnBattleWidgetConstruct(UserWidget* widget)
{
	battleWidget->InitCharacterInfos(playerCharacters);
	if (PlayerActionsMenu* playerActionsMenu = battleWidget->GetPlayerActionsMenu())
	{
		OnPlayerActionsMenuConstructHandle = playerActionsMenu->OnConstruct.Bind(this, &BattleManager::OnPlayerActionsMenuConstruct);
	}

}

void BattleManager::OnPlayerActionsMenuConstruct(UserWidget* widget)
{
	if (PlayerActionsMenu* playerActionsMenu = battleWidget->GetPlayerActionsMenu())
	{
		playerActionsMenu->OnConstruct.Unbind(OnPlayerActionsMenuConstructHandle);
		playerActionsMenu->Init(this);
	}
}

void BattleManager::SetCurrentAbility(Ability* inAbility)
{ 
	currentAbilityWithActorTarget = dynamic_cast<AbilityWithActorTarget*>(inAbility);
	if (currentAbilityWithActorTarget)
	{
		currentState = BattleState::WAIT_FOR_TARGET;
		if (battleWidget)
		{
			battleWidget->HidePlayerActionsMenu();
		}
	}
	else
	{
		inAbility->Execute();
	}
}

void BattleManager::SetPlayerController(PlayerController* inPlayerController)
{
	if (playerController)
	{
		playerController->OnRightClick.Unbind(OnRightClickHandle);
	}
	
	playerController = inPlayerController;

	if (playerController)
	{
		OnRightClickHandle = playerController->OnRightClick.Bind(this, &BattleManager::OnRightClick);
	}
}

void BattleManager::OnRightClick()
{
	if (currentState == BattleState::WAIT_FOR_TARGET)
	{
		if (battleWidget)
		{
			currentAbilityWithActorTarget = nullptr;
			currentState = BattleState::WAIT_FOR_ACTION_SELECTION;
			if (battleWidget)
			{
				battleWidget->ShowPlayerActionsMenu(dynamic_cast<PlayerCharacter*>(currentCharacter));
			}
		}
	}
}